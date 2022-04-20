void Body::Initialize(BodyType type, const glm::vec2 &size) {
  m_type = type;
  m_size = size;
}

void Body::Update(Position *position, float dt) {
  m_max = position->m_position + m_size;
  m_min = position->m_position;
}