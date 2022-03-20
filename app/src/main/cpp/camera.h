struct Camera {
  bool Initialize();
  void Update(float dt);
  void Set(const glm::vec2& position);

  glm::vec2 m_velocity;
  glm::mat4 m_view;
  glm::vec2 m_position;
  glm::vec2 m_target;
};