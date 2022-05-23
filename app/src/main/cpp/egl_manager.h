struct EglManager {
  void Initialize(ANativeWindow *window);
  void Shutdown();

  EGLDisplay m_display;
  EGLSurface m_surface;
  EGLContext m_context;
};