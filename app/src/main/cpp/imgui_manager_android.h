struct ImGuiManagerAndroid : public ImGuiManager {
  void Initialize(ANativeWindow *window);
  void Shutdown();
  void RenderBegin() override; // NOTE(Vlad): Potentially slow function call due to virtual
};