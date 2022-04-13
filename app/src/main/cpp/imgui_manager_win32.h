struct ImGuiManagerWin32 : public ImGuiManager {
  void Initialize(GLFWwindow *window);
  void Shutdown();
  void RenderBegin();
};