#include "main.h"
#include "imgui/imgui.cpp"
#include "imgui/imgui_demo.cpp"
#include "imgui/imgui_draw.cpp"
#ifdef __ANDROID__
  #include "imgui/imgui_impl_android.cpp"
#elif defined _WIN32
  #include "imgui/imgui_impl_glfw.cpp"
#endif

#include "imgui/imgui_impl_opengl3.cpp"
#include "imgui/imgui_tables.cpp"
#include "imgui/imgui_widgets.cpp"

#include "log.cpp"
#include "utility.cpp"
#include "time.cpp"
#include "vertex_buffer_layout.cpp"
#include "vertex_buffer.cpp"
#include "index_buffer.cpp"
#include "vertex_array.cpp"
#include "box.cpp"

#ifdef __ANDROID__
  #include "android_manager.cpp"
  #include "egl_manager.cpp"
#elif defined _WIN32
  #include "win32_manager.cpp"
  #include "glfw_manager.cpp"
#endif

#include "state.cpp"
#include "shader.cpp"
#include "program.cpp"
#include "texture.cpp"
#include "animation.cpp"
#include "position.cpp"
#include "follow_system.cpp"
#include "body.cpp"
#include "movement.cpp"
#include "camera_system.cpp"
#include "control.cpp"
#include "renderer_system.cpp"
#include "collision_system.cpp"
#include "physics_system.cpp"
#include "entity_manager.cpp"
#include "imgui_manager.cpp"
#ifdef __ANDROID__
  #include "imgui_manager_android.cpp"
#elif defined _WIN32
  #include "imgui_manager_win32.cpp"
#endif

void Initialize() {
  stbds_rand_seed(timeGetTime());
}

// TODO: Rework code, make initialization the same for two platforms
// TODO: Link Program and VertexBufferLayout together i guess?
// TODO: Increase complexity, see something that is bad, (aslo allocate on stack)
// TODO: Create vertex buffers using texture width and height?
// TODO: Instead of return codes, just make and assertion and terminate the programm if error is hard

#ifdef __ANDROID__
void android_main(struct android_app *app) {
  EglManager egl_manager;     // Initialization in "android_manager"
  ImGuiManager imgui_manager; // Initialization in "android_manager"
  Game game; // Initialization in "android_manager"

  AndroidManager android_manager;
  {
    android_manager.Initialize(app, &egl_manager, &imgui_manager, &game);
    android_manager.Run(app);
  }
}
#elif defined _WIN32

int main() {
  Initialize();

  GLFWManager glfw_manager;
  if (!glfw_manager.Initialize(1920, 1080, "Game")) {
    return -1;
  }

  ImGuiManagerWin32 imgui_manager_win32;
  imgui_manager_win32.Initialize(glfw_manager.m_window);

  // TODO: Initialize everything else here
  Shader vertex_shader;
  {
    const char *vertex_shader_code = R"(#version 330 core
                                     layout(location = 0) in vec4 position;
                                     layout(location = 1) in vec2 tex;

                                     out vec2 v_Tex;

                                     uniform mat4 u_MVP;

                                     void main() {
                                     gl_Position = u_MVP * position;
                                     v_Tex = tex;
                                     })";
    vertex_shader.Initialize(vertex_shader_code, GL_VERTEX_SHADER);
  }

  Shader fragment_shader;
  {
    const char *fragment_shader_code = R"(#version 330 core
        precision mediump float;
        layout(location = 0) out vec4 color;

        in vec2 v_Tex;

        uniform sampler2D u_Texture;

        void main() {
        vec4 texCoord = texture(u_Texture, v_Tex);
        color = texCoord;
        })";
    fragment_shader.Initialize(fragment_shader_code, GL_FRAGMENT_SHADER);
  }

  Program program;
  {
    program.Initialize();
    program.AddShader(&vertex_shader);
    program.AddShader(&fragment_shader);
    program.Link();
  }

  IndexBuffer index_buffer;
  index_buffer.Initialize();

  VertexBufferLayout vertex_buffer_layout;
  vertex_buffer_layout.Initialize();

  // Systems
  Position camera_position;
  camera_position.Initialize({0, 0});

  CameraSystem camera_system;
  camera_system.Initialize(&glfw_manager, &camera_position);

  RendererSystem renderer_system;
  renderer_system.Initialize(&glfw_manager);

  PhysicsSystem physics_system;
  physics_system.Initialize({0, -4.8f});

  CollisionSystem collision_system;
  collision_system.Initialize();

  FollowSystem follow_system;
  follow_system.Initialize(&glfw_manager);

  EntityManager entity_manager;
  entity_manager.Initialize(&camera_system, &renderer_system, &physics_system, &collision_system, &follow_system);

  Control control; // TODO: Make it that way, so the user can type code here and select components he needs for movement manipulation
  control.Initialize(&glfw_manager, 200.0f);

  // Background
  Texture background_texture;
  background_texture.Initialize("..\\assets\\background.png");

  Box background_box;
  VertexArray background_vertex_array;
  float background_width = glfw_manager.m_width;
  float background_height = glfw_manager.m_height;
  {
    VertexBuffer vertex_buffer;
    vertex_buffer.Initialize(background_width, background_height);

    // Vertex buffer layout
    vertex_buffer_layout.Push(GL_FLOAT, 2);
    vertex_buffer_layout.Push(GL_FLOAT, 2);

    // Vertex array
    background_vertex_array.Initialize();
    background_vertex_array.AddBuffer(&vertex_buffer, &vertex_buffer_layout);

    background_box.Initialize(&index_buffer, &background_vertex_array);
  }

  Position background_position;
  background_position.Initialize({0, 0});

  entity_manager.AddBox(0, &background_box);
  entity_manager.AddTexture(0, &background_texture);
  entity_manager.AddProgram(0, &program);
  entity_manager.AddPosition(0, &background_position);
  entity_manager.AddToRenderer(0);

  // Player
  Texture *player_idle = NULL;
  arrsetlen(player_idle, 4);
  char buffer[128];
  for (int i = 0; i < arrlen(player_idle); ++i) {
    (void)snprintf(buffer, 128, "..\\assets\\player\\idle\\%d.png", i);
    player_idle[i].Initialize(buffer);
  }

  Texture *player_run = NULL;
  arrsetlen(player_run, 8);
  for (int i = 0; i < arrlen(player_run); ++i) {
    (void)snprintf(buffer, 128, "..\\assets\\player\\run\\%d.png", i);
    player_run[i].Initialize(buffer);
  }

  Animation player_animation;
  player_animation.Initialize();
  player_animation.Add(0, player_idle);
  player_animation.Add(1, player_run);

  Box player_box;
  VertexArray player_vertex_array;
  float player_width = player_idle[0].m_width;
  float player_height = player_idle[0].m_height;
  {
    VertexBuffer vertex_buffer;
    vertex_buffer.Initialize(player_width, player_height);

    player_vertex_array.Initialize();
    player_vertex_array.AddBuffer(&vertex_buffer, &vertex_buffer_layout);

    player_box.Initialize(&index_buffer, &player_vertex_array);
  }

  Position player_position;
  player_position.Initialize({glfw_manager.m_width * 0.5f, 80});

  Movement player_movement;
  player_movement.Initialize({10, 0}, {10, 0}, 1.0f, 0);

  Body player_body;
  player_body.Initialize({player_width, player_height});

  entity_manager.AddBox(1, &player_box);
  entity_manager.AddAnimation(1, &player_animation);
  entity_manager.AddControl(1, &control);
  entity_manager.AddProgram(1, &program);
  entity_manager.AddPosition(1, &player_position);
  entity_manager.AddMovement(1, &player_movement);
  entity_manager.AddBody(1, &player_body);
  entity_manager.AddToRenderer(1);
  entity_manager.AddToCollision(1, 2);

  // Bear
  Texture *bear_run = NULL;
  arrsetlen(bear_run, 4);
  for (int i = 0; i < arrlen(bear_run); ++i) {
    (void)snprintf(buffer, 128, "..\\assets\\bear\\%d.png", i);
    bear_run[i].Initialize(buffer);
  }

  Animation bear_animation;
  bear_animation.Initialize();
  bear_animation.Add(0, bear_run);

  Box bear_box;
  VertexArray bear_vertex_array;
  float bear_width = bear_run[0].m_width;
  float bear_height = bear_run[0].m_height;
  {
    VertexBuffer vertex_buffer;
    vertex_buffer.Initialize(player_width, player_height);

    bear_vertex_array.Initialize();
    bear_vertex_array.AddBuffer(&vertex_buffer, &vertex_buffer_layout);

    bear_box.Initialize(&index_buffer, &bear_vertex_array);
  }

  Position bear_position;
  bear_position.Initialize({800, 800});

  Movement bear_movement;
  bear_movement.Initialize({10, 0}, {10, 0}, 1.0f, 0);

  Body bear_body;
  bear_body.Initialize({bear_width, bear_height});

  entity_manager.AddBox(2, &bear_box);
  entity_manager.AddAnimation(2, &bear_animation);
  entity_manager.AddProgram(2, &program);
  entity_manager.AddPosition(2, &bear_position);
  entity_manager.AddMovement(2, &bear_movement);
  entity_manager.AddBody(2, &bear_body);
  entity_manager.AddToRenderer(2);
  entity_manager.AddToPhysics(2);

  // Callbacks
  collision_system.SetOnCollideCallback([&](int a, int b) {
    Position *position = hmget(entity_manager.m_positions, b);

    position->m_position = {800, 800};
  });

  Time time;
  time.Initialize();

  Win32Manager win32_manager;
  win32_manager.Initialize(&glfw_manager, &time, &imgui_manager_win32, &entity_manager);
  win32_manager.Run();

  ExitProcess(0);
}

#endif