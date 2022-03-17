AndroidManager *AndroidManager::m_android_manager = nullptr;

AndroidManager::AndroidManager() { m_android_manager = this; }

void OnAppCmd_Static(struct android_app *app, int32_t app_cmd) {
  AndroidManager::m_android_manager->OnAppCmd(app, app_cmd);
}

int32_t OnInputEvent_Static(struct android_app *app, AInputEvent *input_event) {
  return ImGui_ImplAndroid_HandleInputEvent(input_event);
}

void AndroidManager::OnAppCmd(struct android_app *app, int32_t app_cmd) {
  switch (app_cmd) {
  case APP_CMD_SAVE_STATE:
    break;
  case APP_CMD_INIT_WINDOW:
    OnInitialize(app);
    break;
  case APP_CMD_TERM_WINDOW:
    OnShutdown(app);
    break;
  case APP_CMD_GAINED_FOCUS:
    break;
  case APP_CMD_LOST_FOCUS:
    break;
  }
}

void AndroidManager::OnInitialize(struct android_app *app) {
  if (Global_IsInitialized)
    return;

  ANativeWindow_acquire(app->window);

  m_egl->Initialize(app);
  m_imgui_manager->Initialize(app);

  // TODO: Initialize everything else here
  static Shader vertex_shader;
  {
    const char *vertex_shader_code = "#version 300 es\n"
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

  static Shader fragment_shader;
  {
    const char *fragment_shader_code = "#version 300 es\n"
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

  static Program program;
  {
    program.Initialize();
    program.AddShader(&vertex_shader);
    program.AddShader(&fragment_shader);
    program.Link();
  }

  static Texture texture;
  {
    void *data;
    int length = Utility::GetAssetData(asset_manager, "background.png", &data);
    texture.Initialize(data, length);
  }

  static Box box;
  static VertexBuffer vertex_buffer;
  static IndexBuffer index_buffer;
  static VertexBufferLayout vertex_buffer_layout;
  static VertexArray vertex_array;
  int32_t width = ANativeWindow_getWidth(app->window);
  int32_t height = ANativeWindow_getHeight(app->window);
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

  static Background background;
  background.Initialize(&box, &texture);

  m_game->Initialize(&program, &background);

  Global_IsInitialized = true;
}

void AndroidManager::OnShutdown(struct android_app *app) {
  if (!Global_IsInitialized)
    return;

  m_imgui_manager->Shutdown();
  m_egl->Shutdown(app);

  ANativeWindow_release(app->window);

  Global_IsInitialized = false;
}

bool AndroidManager::Initialize(struct android_app *app, EglManager *egl_manager,
                            ImGuiManager *imgui_manager, Game *game) {
  app->onAppCmd = OnAppCmd_Static;
  app->onInputEvent = OnInputEvent_Static;

  m_imgui_manager = imgui_manager;
  m_egl_manager = egl_manager;
  m_game = game;

  return true;
}

void AndroidManager::Render(struct android_app *app) {
  if (m_egl->m_egl_display == EGL_NO_DISPLAY)
    return;

  m_imgui_manager->RenderBegin(app); // NOTE(Vlad): May be specifi to OS
  m_imgui_manager->Render();
  m_game->Render();

  eglSwapBuffers(m_egl->m_egl_display, m_egl->m_egl_surface);
}

void AppManager::Run(struct android_app *app) {
  while (true) {
    int out_events;
    struct android_poll_source *out_data;

    // Poll all events. If the app is not visible, this loop blocks until
    // Global_IsInitialized == true.
    while (ALooper_pollAll(Global_IsInitialized ? 0 : -1, NULL, &out_events,
                           (void **)&out_data) >= 0) {
      // Process one event
      if (out_data != NULL)
        out_data->process(app, out_data);

      // Exit the app by returning from within the infinite loop
      if (app->destroyRequested != 0) {
        // OnShutdown() should have been called already while processing the
        // app command APP_CMD_TERM_WINDOW. But we play save here
        if (!Global_IsInitialized)
          OnShutdown(app);

        return;
      }
    }

    // Initiate a new frame
    Render(app);
  }
}