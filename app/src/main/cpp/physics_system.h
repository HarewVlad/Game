struct PhysicsSystem {
  void Initialize(const glm::vec2& gravity);
  inline void Update(Movement *movement, float dt);

  glm::vec2 m_gravity;
};