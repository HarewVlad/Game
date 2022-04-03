bool Physics::Initialize() {
  return true;
}

void Physics::Update(Position *position, Movement *movement, float dt) {
  position->m_position += (movement->m_velocity * dt + movement->m_acceleration * dt * dt * 0.5f);
  movement->m_velocity *= powf(movement->m_damping, dt);
}