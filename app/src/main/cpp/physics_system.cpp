void PhysicsSystem::Initialize(const glm::vec2& gravity) {
  m_gravity = gravity;
}

void PhysicsSystem::Update(Movement *movement, float dt) {
  movement->m_acceleration += m_gravity;
}