struct Win32Manager {
  void Initialize(GLFWManager *glfw_manager, Time *time,
                  EntityManager *entity_manager);
  void Shutdown();
  void Run();
  void Render();
  void Update(float dt);

  GLFWManager *m_glfw_manager;
  Time *m_time;
  EntityManager *m_entity_manager;
};