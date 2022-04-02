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

#include "shader.cpp"
#include "program.cpp"
// #include "texture_manager.cpp"
#include "texture.cpp"
#include "animation.cpp"
#include "position.cpp"
#include "movement.cpp"
#include "camera.cpp"
#include "game.cpp"
#include "control.cpp"
#include "renderer.cpp"
#include "entity_manager.cpp"
// Include your game files here
//
#include "imgui_manager.cpp"

#ifdef __ANDROID__
  #include "imgui_manager_android.cpp"
#elif defined _WIN32
  #include "imgui_manager_win32.cpp"
#endif

#include <vector>

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

  std::vector<int> test;
  for (int i = 0; i < (int)test.size() - 1; ++i) {
    int a = 10;
  }

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

  Camera camera;
  camera.Initialize();

  EntityManager entity_manager;
  entity_manager.Initialize();

  IndexBuffer index_buffer;
  index_buffer.Initialize();

  VertexBufferLayout vertex_buffer_layout;
  vertex_buffer_layout.Initialize();

  Box background_box;
  VertexArray background_vertex_array;
  {
    int width = glfw_manager.m_width / 2;
    int height = glfw_manager.m_height / 2;
    VertexBuffer vertex_buffer;
    vertex_buffer.Initialize(width, height);

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
  Texture player_textures[4] = {};
  char buffer[128];
  for (int i = 0; i < sizeof(player_textures) / sizeof(Texture); ++i) {
    (void)snprintf(buffer, 128, "..\\assets\\player\\idle\\%d.png", i);
    player_textures[i].Initialize(buffer);
  }

  Box player_box;
  VertexArray player_vertex_array;
  {
    int width = player_textures[0].m_width;
    int height = player_textures[0].m_height;
    VertexBuffer vertex_buffer;
    vertex_buffer.Initialize(width, height);

    player_vertex_array.Initialize();
    player_vertex_array.AddBuffer(&vertex_buffer, &vertex_buffer_layout);

    player_box.Initialize(&index_buffer, &player_vertex_array);
  }

  Animation player_animation;
  player_animation.Initialize();
  player_animation.Add(&player_textures[0], sizeof(player_textures) / sizeof(Texture));

  Control control;
  control.Initialize(&glfw_manager);

  Renderer renderer;
  renderer.Initialize(&glfw_manager);

  Position background_position;
  background_position.Initialize({glfw_manager.m_width / 2, glfw_manager.m_height / 2});

  Position player_position;
  player_position.Initialize({100, 100});

  Movement player_movement;
  player_movement.Initialize({10, 0}, {10, 0}, 0.1f);

  // Background
  entity_manager.AddBox(0, &background_box);
  entity_manager.AddTexture(0, &background_texture);
  entity_manager.AddRenderer(0, &renderer);
  entity_manager.AddProgram(0, &program);
  entity_manager.AddCamera(0, &camera);
  entity_manager.AddPosition(0, &background_position);

  // Player
  entity_manager.AddBox(1, &player_box);
  entity_manager.AddAnimation(1, &player_animation);
  entity_manager.AddControl(1, &control);
  entity_manager.AddCamera(1, &camera);
  entity_manager.AddRenderer(1, &renderer);
  entity_manager.AddProgram(1, &program);
  entity_manager.AddPosition(1, &player_position);
  entity_manager.AddMovement(1, &player_movement);

  Win32Manager win32_manager;
  {
    win32_manager.Initialize(&glfw_manager, &imgui_manager_win32, &camera, &entity_manager);
    win32_manager.Run();
  }

  ExitProcess(0);
}

#endif