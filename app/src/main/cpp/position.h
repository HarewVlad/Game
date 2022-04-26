struct Position {
  void Initialize(const glm::vec2& position);
  inline glm::mat4 GetModel();

  glm::vec2 m_position;
};