// NOTE(Vlad): "On" prefix because it is event =)

struct WindowManagerAndroid : public WindowManager {
  void Initialize(struct android_app *app, EglManager *egl_manager);
  void OnInitialize();
  void OnShutdown();

  static void OnAppCmd(struct android_app *app, int32_t app_cmd);
  static int32_t OnInputEvent(struct android_app *app, AInputEvent *input_event);

  bool WindowShouldClose() override;
  bool IsWindowFocused() override;
  void SwapBuffers() override;
  void PollEvents() override;

  EglManager *m_egl_manager;
  android_app *m_app;
};