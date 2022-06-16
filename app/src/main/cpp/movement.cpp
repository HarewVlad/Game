void Movement::Initialize(const glm::vec2 &velocity, const glm::vec2 &acceleration, float mass, float damping) {
  m_velocity = velocity;
  m_acceleration = acceleration;
  m_damping = damping;
  m_mass = mass;
  m_imass = 1.0f / mass;
}