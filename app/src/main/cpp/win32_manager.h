struct Win32Manager {
  bool Initialize(GLFWManager *glfw_manager, ImGuiManagerWin32 *imgui_manager_win32, Game *game);
  void Shutdown();
  void Run();
  void Render();
  void Update(float dt);

  GLFWManager *m_glfw_manager;
  ImGuiManagerWin32 *m_imgui_manager_win32;
  Game *m_game; // NOTE(Vlad): Basically you place all you data in Game structure
};