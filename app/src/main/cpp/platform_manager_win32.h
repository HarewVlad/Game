struct PlatformManagerWin32 : public PlatformManager {
  void Initialize(const glm::vec2& size, const char *title);
  bool ShouldClose() override;
  int GetWindowFlag(int flag);
  bool IsFocused() override;
  void SwapBuffers() override;
  void PollEvents() override;

  static void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);
  static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
};