bool Win32Manager::Initialize(GLFWManager *glfw_manager, ImGuiManagerWin32 *imgui_manager_win32, Game *game) {
  m_glfw_manager = glfw_manager;
  m_imgui_manager_win32 = imgui_manager_win32;
  m_game = game;

  return true;
}

void Win32Manager::Run() {
  float last_frame_time = 0.0f;
  while (!glfwWindowShouldClose(m_glfw_manager->m_window)) {
    float time = static_cast<float>(glfwGetTime());
    float dt = time - last_frame_time;
    last_frame_time = time;

    Update(dt);
    Render();

    glfwSwapBuffers(m_glfw_manager->m_window);
    glfwPollEvents();
  }
}

void Win32Manager::Render() {
  glCall(glClearColor(0.5, 0.5, 0, 1.0f));
  glCall(glClear(GL_COLOR_BUFFER_BIT));

  glCall(glEnable(GL_BLEND));
  glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  m_game->Render();
  m_imgui_manager_win32->RenderBegin(); // NOTE(Vlad): This part may be specifi to OS
  m_imgui_manager_win32->Render();
}

void Win32Manager::Update(float dt) {
  m_game->Update(dt);
}

void Win32Manager::Shutdown() {
  m_glfw_manager->Shutdown();
  m_imgui_manager_win32->Shutdown();
}