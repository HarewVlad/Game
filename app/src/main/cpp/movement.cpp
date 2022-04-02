bool Movement::Initialize(const glm::vec2 &velocity, const glm::vec2 &acceleration, float damping) {
  m_velocity = velocity;
  m_acceleration = acceleration;
  m_damping = damping;

  return true;
}

void Movement::Update(Position *position, float dt) { // TODO: Move this calculation to Physics component later
  // TODO: Add forces to acceleration later + mass
  position->m_position += (m_velocity * dt + m_acceleration * dt * dt * 0.5f);
  m_velocity *= powf(m_damping, dt); // NOTE: Consumes some computation power
}