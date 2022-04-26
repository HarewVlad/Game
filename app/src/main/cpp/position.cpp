void Position::Initialize(const glm::vec2 &position) { 
  m_position = position;
}

inline glm::mat4 Position::GetModel() {
  return glm::translate(Global_Identity, glm::vec3(m_position, 0));
}