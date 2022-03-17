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
#include "background.cpp"
#include "game.cpp"
#include "imgui_manager.cpp"

#ifdef __ANDROID__
  #include "imgui_manager_android.cpp"
#elif defined _WIN32
  #include "imgui_manager_win32.cpp"
#endif

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
  GLFWManager glfw_manager;
  if (!glfw_manager.Initialize(1024, 720, "Game")) {
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

  Box box;
  VertexBuffer vertex_buffer;
  IndexBuffer index_buffer;
  VertexBufferLayout vertex_buffer_layout;
  VertexArray vertex_array;
  int32_t width = glfw_manager.m_width * 2;
  int32_t height = glfw_manager.m_height * 2;
  {
    // Vertex buffer
    std::vector<float> vertices = {-width / 2.0f, -height / 2.0f, 0.0f, 0.0f,
                                   -width / 2.0f, height / 2.0f,  0.0f, 1.0f,
                                   width / 2.0f,  height / 2.0f,  1.0f, 1.0f,
                                   width / 2.0f,  -height / 2.0f, 1.0f, 0.0f};
    vertex_buffer.Initialize(&vertices[0], sizeof(float) * vertices.size());

    // Index buffer
    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};
    index_buffer.Initialize(&indices[0], indices.size());

    // Vertex array
    vertex_buffer_layout.Push<float>(2);
    vertex_buffer_layout.Push<float>(2);
    vertex_array.Initialize();
    vertex_array.AddBuffer(&vertex_buffer, &vertex_buffer_layout);

    box.Initialize(&index_buffer, &vertex_array);
  }

  Background background;
  background.Initialize(&box, &texture);

  Game game;
  game.Initialize(&program, &background);

  Win32Manager win32_manager;
  {
    win32_manager.Initialize(&glfw_manager, &imgui_manager_win32, &game);
    win32_manager.Run();
  }
}

#endif