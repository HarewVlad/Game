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
#include "input.cpp"
#include "camera.cpp"
#include "background.cpp"
#include "game.cpp"
#include "entity_manager.cpp"
// Include your game here
#include "falling_creatures/player.cpp"
#include "falling_creatures/falling_creatures.cpp"
//
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

  
  // TextureManager texture_manager;
  // texture_manager.Initialize();
  // texture_manager.Add("background", "..\\assets\\background.png");

  Camera camera;
  camera.Initialize();

  Input input;
  input.Initialize(&glfw_manager);
  int keys[] = {'W', 'A', 'S', 'D'};
  input.Add(&keys[0], sizeof(keys) / sizeof(int));

  EntityManager entity_manager;
  entity_manager.Initialize();

  IndexBuffer index_buffer;
  index_buffer.Initialize();

  VertexBufferLayout vertex_buffer_layout;
  vertex_buffer_layout.Initialize();

  Box background_box;
  VertexArray background_vertex_array;
  {
    int x = glfw_manager.m_width / 2;
    int y = glfw_manager.m_height / 2;
    VertexBuffer vertex_buffer;
    vertex_buffer.Initialize(x, y);

    // Vertex buffer layout
    vertex_buffer_layout.Push(GL_FLOAT, 2);
    vertex_buffer_layout.Push(GL_FLOAT, 2);

    // Vertex array
    background_vertex_array.Initialize();
    background_vertex_array.AddBuffer(&vertex_buffer, &vertex_buffer_layout);

    background_box.Initialize(&index_buffer, &background_vertex_array, x, y);
  }

  Texture background_texture;
  background_texture.Initialize("..\\assets\\background.png");

  Background background;
  background.Initialize(&glfw_manager, &program, &camera, &background_box, &background_texture);
  
  Box player_box;
  VertexArray player_vertex_array;
  {
    int x = 100;
    int y = 100;
    VertexBuffer vertex_buffer;
    vertex_buffer.Initialize(x, y);

    player_vertex_array.Initialize();
    player_vertex_array.AddBuffer(&vertex_buffer, &vertex_buffer_layout);

    player_box.Initialize(&index_buffer, &player_vertex_array, x, y);
  }

  Texture player_texture;
  player_texture.Initialize("..\\assets\\player.png");

  // Animation
  Texture player_textures[4] = {};
  char buffer[128];
  for (int i = 0; i < sizeof(player_textures) / sizeof(Texture); ++i) {
    (void)snprintf(buffer, 128, "..\\assets\\player\\idle\\%d.png", i);
    player_textures[i].Initialize(buffer);
  }
  
  Animation player_animation;
  player_animation.Initialize();
  player_animation.Add(&player_textures[0], sizeof(player_textures) / sizeof(Texture));

  Player player;
  player.Initialize(&glfw_manager, &program, &camera, &player_box, &player_animation);

  entity_manager.AddInput((int)EntityId::PLAYER, &player_box, &input);
  entity_manager.AddAnimation((int)EntityId::PLAYER, &player_animation);

  FallingCreatures falling_creatures;
  falling_creatures.Initialize(&background, &player);

  Win32Manager win32_manager;
  {
    win32_manager.Initialize(&glfw_manager, &imgui_manager_win32, &input, &camera, &falling_creatures, &entity_manager);
    win32_manager.Run();
  }

  ExitProcess(0);
}

#endif