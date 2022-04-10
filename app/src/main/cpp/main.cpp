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
  stbds_rand_seed(time(NULL));
}

// TODO: Rework code, make initialization the same for two platforms
// TODO: Link Program and VertexBufferLayout together i guess?
// TODO: Increase complexity, see something that is bad, (aslo allocate on stack)
// TODO: Create vertex buffers using texture width and height?

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
  if (!imgui_manager_win32.Initialize(glfw_manager.m_window)) {
    return -1;
  }

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

  Box background_box;
  VertexArray background_vertex_array;
  float background_width = glfw_manager.m_width / 2;
  float background_height = glfw_manager.m_height / 2;
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

  Texture background_texture;
  background_texture.Initialize("..\\assets\\background.png");

  // Animation
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

  Control control;
  control.Initialize(&glfw_manager);

  Position background_position;
  background_position.Initialize({background_width, background_height});

  Position player_position;
  player_position.Initialize({600, 300});

  Movement player_movement;
  player_movement.Initialize({10, 0}, {10, 0}, 1.0f, 0.1f);

  // Systems
  CameraSystem camera_system;
  camera_system.Initialize(&glfw_manager);

  RendererSystem renderer_system;
  renderer_system.Initialize(&glfw_manager);

  PhysicsSystem physics_system;
  physics_system.Initialize({0, -4.8f});

  CollisionSystem collision_system;
  collision_system.Initialize();
  //

  enum PlayerState {
    IDLE, RUN
  };

  State player_state;

  Body player_body;
  player_body.Initialize(&player_position, {player_width, player_height});

  EntityManager entity_manager;
  entity_manager.Initialize(&camera_system, &renderer_system, &physics_system, &collision_system);

  // Background
  entity_manager.AddBox(0, &background_box);
  entity_manager.AddTexture(0, &background_texture);
  entity_manager.AddProgram(0, &program);
  entity_manager.AddPosition(0, &background_position);
  entity_manager.AddToRenderer(0);

  // Ground
  Texture ground_texture;
  ground_texture.Initialize("..\\assets\\ground.png");

  Box ground_box;
  VertexArray ground_vertex_array;
  float ground_width = ground_texture.m_width;
  float ground_height = ground_texture.m_height;
  {
    VertexBuffer vertex_buffer;
    vertex_buffer.Initialize(ground_width, ground_height);

    ground_vertex_array.Initialize();
    ground_vertex_array.AddBuffer(&vertex_buffer, &vertex_buffer_layout);

    ground_box.Initialize(&index_buffer, &ground_vertex_array);
  }

  Position ground_position;
  ground_position.Initialize({300, 200});

  Body ground_body;
  ground_body.Initialize(&ground_position, {ground_width, ground_height});

  entity_manager.AddBox(1, &ground_box);
  entity_manager.AddTexture(1, &ground_texture);
  entity_manager.AddProgram(1, &program);
  entity_manager.AddPosition(1, &ground_position);
  entity_manager.AddBody(1, &ground_body);
  entity_manager.AddToRenderer(1);
  entity_manager.AddToCollision(1);

  // Player
  entity_manager.AddBox(2, &player_box);
  entity_manager.AddAnimation(2, &player_animation);
  entity_manager.AddControl(2, &control);
  entity_manager.AddProgram(2, &program);
  entity_manager.AddPosition(2, &player_position);
  entity_manager.AddMovement(2, &player_movement);
  entity_manager.AddBody(2, &player_body);
  entity_manager.AddToPhysics(2);
  entity_manager.AddToRenderer(2);
  entity_manager.AddToCollision(2);
  entity_manager.SetToCamera(2);

  Win32Manager win32_manager;
  {
    win32_manager.Initialize(&glfw_manager, &imgui_manager_win32, &entity_manager);
    win32_manager.Run();
  }

  ExitProcess(0);
}

#endif