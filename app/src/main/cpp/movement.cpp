void Movement::Initialize(float mass, float damping) {
  m_damping = damping;
  m_mass = mass;
  m_imass = 1.0f / mass;
}