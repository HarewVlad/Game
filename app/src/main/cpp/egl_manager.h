struct EglManager {
  bool Initialize(struct android_app *app);
  void Shutdown(struct android_app *app);

  EGLDisplay m_egl_display;
  EGLSurface m_egl_surface;
  EGLContext m_egl_context;
};