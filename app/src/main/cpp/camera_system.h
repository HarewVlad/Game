struct CameraSystem {
  bool Initialize(GLFWManager *glfw_manager);
  void Follow(Position *position);
  glm::mat4 GetView();

  GLFWManager *m_glfw_manager;
  glm::mat4 m_view;
  glm::vec2 m_position;
};