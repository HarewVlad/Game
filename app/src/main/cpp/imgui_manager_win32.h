struct ImGuiManagerWin32 : public ImGuiManager {
  bool Initialize(GLFWwindow *window);
  void Shutdown();
  void RenderBegin();
};