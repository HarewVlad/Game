enum BodyType {
  BodyType_Box,
  BodyType_BoundingBox
};

struct Body {
  void Initialize(int type, const glm::vec2 &size);

  int m_type;
  glm::vec2 m_size = {};
};