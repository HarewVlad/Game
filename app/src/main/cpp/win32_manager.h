struct Win32Manager {
  bool Initialize(GLFWManager *glfw_manager,
                  ImGuiManagerWin32 *imgui_manager_win32, Input *input,
                  Camera *camera, EntityManager *entity_manager);
  void Shutdown();
  void Run();
  void Render();
  void Update(float dt);

  GLFWManager *m_glfw_manager;
  ImGuiManagerWin32 *m_imgui_manager_win32;
  Input *m_input;
  Camera *m_camera;
  EntityManager *m_entity_manager;
};