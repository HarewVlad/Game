struct AABB {
  bool Initialize(const glm::vec2 &min, const glm::vec2 &max);
  bool Initialize(Position *position, const glm::vec2 &size);
  glm::vec2 m_min;
  glm::vec2 m_max;
};

struct AABBMap {
  int key;
  AABB *value;
};