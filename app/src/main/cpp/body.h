enum class BodyType {
  NORMAL,
  BOUNDING
};

struct Body {
  void Initialize(BodyType type, const glm::vec2 &size);

  BodyType m_type;
  glm::vec2 m_size;
};