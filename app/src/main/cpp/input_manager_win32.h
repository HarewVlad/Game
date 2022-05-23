struct InputManagerWin32 : public InputManager {
  void Initialize(GLFWwindow *window);
  bool IsKeyPressed(int key) override;

  GLFWwindow *m_window;
};