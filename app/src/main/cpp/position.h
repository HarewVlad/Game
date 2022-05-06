struct Position {
  void Initialize(const glm::vec2& position, const glm::vec2& scale = {1, 1});
  glm::mat4 GetModel() const;

  glm::vec2 m_position;
  glm::vec2 m_scale;
};