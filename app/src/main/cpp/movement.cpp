bool Movement::Initialize(const glm::vec2 &velocity, const glm::vec2 &acceleration, float damping) {
  m_velocity = velocity;
  m_acceleration = acceleration;
  m_damping = damping;

  return true;
}