struct ImGuiManagerAndroid : public ImGuiManager {
  void Initialize(struct android_app *app);
  void Shutdown();
  void RenderBegin(struct android_app *app);
};