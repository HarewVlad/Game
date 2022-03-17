EglManager::EglManager() {
  m_egl_display = EGL_NO_DISPLAY;
  m_egl_surface = EGL_NO_SURFACE;
  m_egl_context = EGL_NO_CONTEXT;
}

void EglManager::Shutdown(struct android_app *app) {
  if (m_egl_display != EGL_NO_DISPLAY) {
    eglMakeCurrent(m_egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

    if (m_egl_context != EGL_NO_CONTEXT)
        eglDestroyContext(m_egl_display, m_egl_context);

    if (m_egl_surface != EGL_NO_SURFACE)
        eglDestroySurface(m_egl_display, m_egl_surface);

    eglTerminate(m_egl_display);
  }

  m_egl_display = EGL_NO_DISPLAY;
  m_egl_context = EGL_NO_CONTEXT;
  m_egl_surface = EGL_NO_SURFACE;
}

bool EglManager::Initialize(struct android_app *app) {
  m_egl_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  if (m_egl_display == EGL_NO_DISPLAY) {
      LOG(LOG_ERROR, Global_LogTag, "%s", "eglGetDisplay(EGL_DEFAULT_DISPLAY) returned EGL_NO_DISPLAY");
      return false;
  }

  if (eglInitialize(m_egl_display, 0, 0) != EGL_TRUE) {
      LOG(LOG_ERROR, Global_LogTag, "%s", "eglInitialize() returned with an error");
      return false;
  }

  const EGLint egl_attributes[] = { EGL_BLUE_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_RED_SIZE, 8, EGL_DEPTH_SIZE, 24, EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_NONE };
  EGLint num_configs = 0;
  if (eglChooseConfig(m_egl_display, egl_attributes, nullptr, 0, &num_configs) != EGL_TRUE) {
      LOG(LOG_ERROR, Global_LogTag, "%s", "eglChooseConfig() returned with an error");
      return false;
  }
  if (num_configs == 0) {
      LOG(LOG_ERROR, Global_LogTag, "%s", "eglChooseConfig() returned 0 matching config");
      return false;
  }

  // Get the first matching config
  EGLConfig egl_config;
  eglChooseConfig(m_egl_display, egl_attributes, &egl_config, 1, &num_configs);
  EGLint egl_format;
  eglGetConfigAttrib(m_egl_display, egl_config, EGL_NATIVE_VISUAL_ID, &egl_format);
  ANativeWindow_setBuffersGeometry(app->window, 0, 0, egl_format);

  const EGLint egl_context_attributes[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
  m_egl_context = eglCreateContext(m_egl_display, egl_config, EGL_NO_CONTEXT, egl_context_attributes);

  if (m_egl_context == EGL_NO_CONTEXT) {
      LOG(LOG_ERROR, Global_LogTag, "%s", "eglCreateContext() returned EGL_NO_CONTEXT");
      return false;
  }

  m_egl_surface = eglCreateWindowSurface(m_egl_display, egl_config, app->window, NULL);
  eglMakeCurrent(m_egl_display, m_egl_surface, m_egl_surface, m_egl_context);

  return true;
}