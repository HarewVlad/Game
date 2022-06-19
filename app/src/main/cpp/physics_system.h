struct PhysicsSystem : public ISystem {
  void Initialize(const glm::vec2& gravity);
  void Update(EntityManager *entity_manager, float dt) override;

  glm::vec2 m_gravity;
};