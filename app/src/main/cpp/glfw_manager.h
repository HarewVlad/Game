struct KeyState {
  int key;
  bool value;
};

struct GLFWManager {
  GLFWManager();
  void Initialize(Size *window_size, glm::mat4 *projection, const char *title);
  void Shutdown();
  void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);
  void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
  bool IsKeyPressed(int key);
  int GetWindowFlag(int flag);
  bool IsWindowFocused();

  static GLFWManager *m_glfw_manager;

  GLFWwindow *m_window;
  KeyState *m_key_state;
  Size *m_window_size;
  glm::mat4 *m_projection;
};