struct CameraSystem {
  void Initialize(const glm::vec2 &xy);
  glm::mat4 GetView() const;

  glm::mat4 m_view;
  glm::vec2 m_xy;
};