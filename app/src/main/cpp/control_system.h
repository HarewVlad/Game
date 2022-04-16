struct ControlSystem {
  void Initialize(GLFWManager *glfw_manager);
  void SetUpdateCallback(const std::function<void(Movement *, State *, float)> update);

  std::function<void(Movement *, State *, float)> m_update;
  GLFWManager *m_glfw_manager;
};