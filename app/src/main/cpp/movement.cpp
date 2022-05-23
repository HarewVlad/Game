void Movement::Initialize(const glm::vec2 &velocity, const glm::vec2 &acceleration, float mass, float damping) {
  m_velocity = velocity;
  m_acceleration = acceleration;
  m_damping = damping;
  m_mass = mass;
}

// TODO: Redo movement and other physics based on BOX2D-lite
void Movement::Update(Position *position, float dt) {
  position->m_xy += m_velocity * dt + m_acceleration * dt * dt * 0.5f;
  m_velocity += m_acceleration * dt;
  m_velocity *= powf(m_damping, dt);
}