struct Camera {
  void Initialize(const glm::vec2 &xy);

  glm::vec2 m_xy;
  glm::mat4 m_view;
};