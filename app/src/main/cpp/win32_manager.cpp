void Win32Manager::Initialize(GLFWManager *glfw_manager, Time *time,
                              EntityManager *entity_manager) {
  m_glfw_manager = glfw_manager;
  m_time = time;
  m_entity_manager = entity_manager;
}

void Win32Manager::Run() {
  int old_time = m_time->GetMilliseconds();
  int extra_time = 0;
  int frame_time = 1000 / MAX_FPS;
  while (!glfwWindowShouldClose(m_glfw_manager->m_window) && Global_GameState != GameState::EXIT) {
    int new_time = m_time->GetMilliseconds();
    int time = new_time - old_time;

    ////// FRAME ///////

    if (m_glfw_manager->IsWindowFocused()) {
      extra_time += time;

      while (extra_time >= frame_time) {
        glfwPollEvents();

        Update(frame_time / 1000.0f);

        extra_time -= frame_time;
      }
      
      Render();
    } else {
      Sleep(5);

      glfwPollEvents();
    }

    glfwSwapBuffers(m_glfw_manager->m_window);

    /////// END FRAME ///////

    old_time = new_time;
  }
}

void Win32Manager::Render() {
  glCall(glClearColor(0.0, 0.0, 0.0, 1.0f));
  glCall(glClear(GL_COLOR_BUFFER_BIT));

  glCall(glEnable(GL_BLEND));
  glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  glViewport(0, 0, m_glfw_manager->m_width, m_glfw_manager->m_height);

  m_entity_manager->Render();
}

void Win32Manager::Update(float dt) {
  m_entity_manager->Update(dt);
}

void Win32Manager::Shutdown() {
  m_glfw_manager->Shutdown();
}