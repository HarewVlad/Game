struct CameraSystem {
  void Initialize(GLFWManager *glfw_manager, Position *position);
  glm::mat4 GetView() const;

  GLFWManager *m_glfw_manager;
  glm::mat4 m_view;
  Position *m_position;
};