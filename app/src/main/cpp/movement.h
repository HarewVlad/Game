struct Movement {
  bool Initialize(const glm::vec2 &velocity, const glm::vec2 &acceleration, float damping);
  void Update(Position *position, float dt);

  glm::vec2 m_velocity;
  glm::vec2 m_acceleration;
  float m_damping;
};

struct MovementMap {
  int key;
  Movement *value;
};