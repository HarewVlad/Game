int32_t WindowManagerAndroid::OnInputEvent(struct android_app *app, AInputEvent *input_event) {
  return ImGui_ImplAndroid_HandleInputEvent(input_event);
}

void WindowManagerAndroid::OnAppCmd(struct android_app *app, int32_t app_cmd) {
  WindowManagerAndroid *window_manager_android = (WindowManagerAndroid *)app->userData;

  switch (app_cmd) {
  case APP_CMD_SAVE_STATE:
    break;
  case APP_CMD_INIT_WINDOW:
    window_manager_android->OnInitialize();
    Global_GameState = GameState::READY;
    break;
  case APP_CMD_TERM_WINDOW:    
    window_manager_android->OnShutdown();
    Global_GameState = GameState::EXIT;
    break;
  case APP_CMD_GAINED_FOCUS:
    break;
  case APP_CMD_LOST_FOCUS:
    break;
  }
}

void WindowManagerAndroid::OnInitialize() {
  ANativeWindow_acquire(m_app->window);

  int width = ANativeWindow_getWidth(m_app->window);
  int height = ANativeWindow_getHeight(m_app->window);

  m_size = {width, height};
  m_projection =
      glm::ortho(0.0f, static_cast<float>(width), 0.0f,
                 static_cast<float>(height), -1000.0f, 1000.0f);
  m_window = m_app->window;

  m_egl_manager->Initialize(m_app->window);
}

void WindowManagerAndroid::OnShutdown() {
  ANativeWindow_release(m_app->window);

  m_egl_manager->Shutdown();
}

void WindowManagerAndroid::Initialize(struct android_app *app, EglManager *egl_manager) {
  app->userData = this;
  app->onAppCmd = OnAppCmd;
  app->onInputEvent = OnInputEvent;

  m_egl_manager = egl_manager;
  m_app = app;
}

bool WindowManagerAndroid::WindowShouldClose() {
  return m_app->destroyRequested != 0;
}

bool WindowManagerAndroid::IsWindowFocused() {
  // TODO: Fix later
  return true;
}

void WindowManagerAndroid::SwapBuffers() {
  eglSwapBuffers(m_egl_manager->m_display, m_egl_manager->m_surface);
}

void WindowManagerAndroid::PollEvents() {
  int out_events;
  struct android_poll_source *out_data;
  while (ALooper_pollAll(0, NULL, &out_events,
                           (void **)&out_data) >= 0) {
    // Process one event
    if (out_data != NULL)
      out_data->process(m_app, out_data);
  }
}