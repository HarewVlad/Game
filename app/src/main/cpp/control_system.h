struct ControlSystem {
  void Initialize(GLFWManager *glfw_manager);
  void SetUpdate(const std::function<void(int, float)> update);

  std::function<void(int, float)> m_update;
  GLFWManager *m_glfw_manager;
};