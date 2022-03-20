struct GLFWManager {
  GLFWManager();
  bool Initialize(int width, int height, const char *title);
  void Shutdown();
  void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);

  static GLFWManager *m_glfw_manager;

  GLFWwindow *m_window;
  int m_width;
  int m_height;
  glm::mat4 m_projection;
};