bool Body::Initialize(const glm::vec2 &min, const glm::vec2 &max) {
  m_min = min;
  m_max = max;

  return true;
}

bool Body::Initialize(Position *position, const glm::vec2 &size) {
  m_min = position->m_position;
  m_max = position->m_position + size;

  return true;
}

void Body::Update(Position *position, float dt) {
  m_max = (m_max - m_min) + position->m_position;
  m_min = position->m_position;
}