struct Movement {
  void Initialize(float mass, float damping);

  glm::vec2 m_velocity;
  glm::vec2 m_acceleration;
  glm::vec2 m_force;
  float m_damping;
  float m_mass;
  float m_imass;
};