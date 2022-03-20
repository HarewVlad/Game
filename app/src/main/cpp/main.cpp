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
#include "input.cpp"
#include "camera.cpp"
#include "background.cpp"
#include "game.cpp"
// Include your game here
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
    const char *vertex_shader_code = "#version 330 core\n"
                                     "layout(location = 0) in vec4 position;\n"
                                     "layout(location = 1) in vec2 tex;\n"

                                     "out vec2 v_Tex;\n"

                                     "uniform mat4 u_MVP;\n"

                                     "void main() {\n"
                                     "gl_Position = u_MVP * position;\n"
                                     "v_Tex = tex;\n"
                                     "}";
    vertex_shader.Initialize(vertex_shader_code, GL_VERTEX_SHADER);
  }

  Shader fragment_shader;
  {
    const char *fragment_shader_code = "#version 330 core\n"
        "precision mediump float;"
        "layout(location = 0) out vec4 color;\n"

        "in vec2 v_Tex;\n"

        "uniform sampler2D u_Texture;\n"

        "void main() {\n"
        "vec4 texCoord = texture(u_Texture, v_Tex);\n"
        "color = texCoord;\n"
        "}";
    fragment_shader.Initialize(fragment_shader_code, GL_FRAGMENT_SHADER);
  }

  Program program;
  {
    program.Initialize();
    program.AddShader(&vertex_shader);
    program.AddShader(&fragment_shader);
    program.Link();
  }

  Texture texture;
  texture.Initialize("..\\assets\\background.png");
  // TextureManager texture_manager;
  // texture_manager.Initialize();
  // texture_manager.Add("background", "..\\assets\\background.png");

  Box box;
  VertexBuffer vertex_buffer;
  IndexBuffer index_buffer;
  VertexBufferLayout vertex_buffer_layout;
  vertex_buffer_layout.Initialize();
  VertexArray vertex_array;
  int32_t x = glfw_manager.m_width / 2;
  int32_t y = glfw_manager.m_height / 2;
  {
    vertex_buffer.Initialize(x, y);
    index_buffer.Initialize();

    // Vertex array
    vertex_buffer_layout.Push(GL_FLOAT, 2);
    vertex_buffer_layout.Push(GL_FLOAT, 2);
    vertex_array.Initialize();
    vertex_array.AddBuffer(&vertex_buffer, &vertex_buffer_layout);

    box.Initialize(&index_buffer, &vertex_array, x, y);
  }

  Camera camera;
  camera.Initialize();

  Background background;
  background.Initialize(&glfw_manager, &program, &camera, &box, &texture);

  Input input;
  input.Initialize(&glfw_manager);
  int keys[] = {'W', 'A', 'S', 'D'};
  input.Add(&keys[0], sizeof(keys) / sizeof(int));

  FallingCreatures falling_creatures;
  falling_creatures.Initialize(&background);

  Win32Manager win32_manager;
  {
    win32_manager.Initialize(&glfw_manager, &imgui_manager_win32, &input, &camera, &falling_creatures);
    win32_manager.Run();
  }

  ExitProcess(0);
}

#endif