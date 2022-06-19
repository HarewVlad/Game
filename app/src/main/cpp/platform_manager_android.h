// NOTE(Vlad): "On" prefix because it is event =)

struct PlatformManagerAndroid : public PlatformManager {
  void Initialize(struct android_app *app, EglManager *egl_manager);
  void OnInitialize();
  void OnShutdown();
  bool ShouldClose() override;
  bool IsFocused() override;
  void SwapBuffers() override;
  void PollEvents() override;

  static void OnAppCmd(struct android_app *app, int32_t app_cmd);
  static int32_t OnInputEvent(struct android_app *app, AInputEvent *input_event);

  EglManager *m_egl_manager;
  android_app *m_app;
};