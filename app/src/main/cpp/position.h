struct Position {
  void Initialize(const glm::vec2& position);
  void MoveX(float x);
  void MoveY(float y);
  inline glm::mat4 GetModel();

  glm::vec2 m_position;
  // float m_angle ...
};