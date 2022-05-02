void Position::Initialize(const glm::vec2 &position, const glm::vec2 &scale) { 
  m_position = position;
  m_scale = scale;
}

inline glm::mat4 Position::GetModel() {
  return glm::translate(IDENTITY, glm::vec3(m_position, 0)) * glm::scale(IDENTITY, glm::vec3(m_scale, 1.0f));
}