struct CameraSystem {
  bool Initialize(GLFWManager *glfw_manager, Position *position);
  void Follow(Position *position);
  glm::mat4 GetView();

  GLFWManager *m_glfw_manager;
  glm::mat4 m_view;
  Position *m_position; // NOTE(Vlad): I guess we need to remove it?
};