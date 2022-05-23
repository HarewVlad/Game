struct Position {
  void Initialize(const glm::vec2& xy);
  glm::mat4 GetModel() const;

  glm::vec2 m_xy;
};