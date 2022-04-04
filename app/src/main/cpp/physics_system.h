struct PhysicsSystem {
  bool Initialize(const glm::vec2& gravity);
  void Update(Movement *movement, float dt);

  glm::vec2 m_gravity;
};