void Position::Initialize(const glm::vec2 &position, const glm::vec2 &scale) { 
  m_position = position;
  m_scale = scale;
}

inline glm::mat4 Position::GetModel() {
  return glm::translate(Global_Identity, glm::vec3(m_position, 0)) * glm::scale(Global_Identity, glm::vec3(m_scale, 1.0f));
}