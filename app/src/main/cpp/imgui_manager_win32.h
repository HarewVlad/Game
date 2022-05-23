struct ImGuiManagerWin32 : public ImGuiManager {
  void Initialize(GLFWwindow *window);
  void Shutdown();
  void RenderBegin() override; // NOTE(Vlad): Potentially slow function call due to virtual
};