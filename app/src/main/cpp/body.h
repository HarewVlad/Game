struct Body {
  bool Initialize(const glm::vec2 &min, const glm::vec2 &max);
  bool Initialize(Position *position, const glm::vec2 &size);
  void Update(Position *position, float dt);
  glm::vec2 m_min;
  glm::vec2 m_max;
};

struct BodyMap {
  int key;
  Body *value;
};