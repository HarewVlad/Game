struct Win32Manager {
  void Initialize(GLFWManager *glfw_manager,
                  ImGuiManagerWin32 *imgui_manager_win32,
                  EntityManager *entity_manager);
  void Shutdown();
  void Run();
  void Render();
  void Update(float dt);

  GLFWManager *m_glfw_manager;
  ImGuiManagerWin32 *m_imgui_manager_win32;
  EntityManager *m_entity_manager;
};