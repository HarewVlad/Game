struct ImGuiManagerAndroid : public ImGuiManager {
  bool Initialize(struct android_app *app);
  void Shutdown();
  void RenderBegin(struct android_app *app) override;
};