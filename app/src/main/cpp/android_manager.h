// NOTE(Vlad): "On" prefix because it is event =)

struct AndroidManager {
  AndroidManager();
  bool Initialize(struct android_app *app, EglManager *egl_manager, ImGuiManager *imgui_manager);
  void OnInitialize(struct android_app *app);
  void OnShutdown(struct android_app *app);
  void Render(struct android_app *app);
  void Run(struct android_app *app);
  void OnAppCmd(struct android_app *app, int32_t app_cmd);

  static AndroidManager *m_android_manager;

  // Modules
  ImGuiManager *m_imgui_manager;
  EglManager *m_egl_manager;
};