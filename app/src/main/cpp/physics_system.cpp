bool PhysicsSystem::Initialize(const glm::vec2& gravity) {
  m_gravity = gravity;
  return true;
}

void PhysicsSystem::Update(Movement *movement, float dt) {
  movement->m_acceleration += m_gravity;
}