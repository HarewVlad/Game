struct WindowManagerWin32 : public WindowManager {
  void Initialize(const glm::vec2& size, const char *title);
  bool WindowShouldClose() override;
  int GetWindowFlag(int flag);
  bool IsWindowFocused() override;
  void SwapBuffers() override;
  void PollEvents() override;

  static void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);
};