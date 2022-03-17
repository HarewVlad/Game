struct GLFWManager {
  bool Initialize(UINT width, UINT height, const char *title);
  void Shutdown();

  GLFWwindow *m_window;
};