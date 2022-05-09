struct Win32Manager {
  void Initialize(GLFWManager *glfw_manager,
                  EntityManager *entity_manager);
  void Shutdown();
  void Run();
  void Render();
  void Update(float dt);

  GLFWManager *m_glfw_manager;
  EntityManager *m_entity_manager;
};