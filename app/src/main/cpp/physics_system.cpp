void PhysicsSystem::Initialize(const glm::vec2& gravity) {
  m_gravity = gravity;
}

void PhysicsSystem::Update(EntityManager *entity_manager, float dt) {
  for (int i = 0; i < arrlen(m_entities); ++i) {
    Entity entity = m_entities[i];

    Movement *movement = entity_manager->GetComponent<Movement>(entity);
    movement->m_acceleration += m_gravity;
  }
}