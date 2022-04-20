enum class BodyType {
  NORMAL,
  BOUNDING
};

struct Body {
  void Initialize(BodyType type, const glm::vec2 &size);
  void Update(Position *position, float dt);

  BodyType m_type;
  glm::vec2 m_size;
  glm::vec2 m_min;
  glm::vec2 m_max;
};

struct BodyMap {
  int key;
  Body *value;
};