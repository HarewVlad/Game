void Position::Initialize(const glm::vec2& xy) {
  m_xy = xy;
}

glm::mat4 Position::GetModel() const {
  return glm::translate(IDENTITY, glm::vec3(m_xy, 0)) /** glm::scale(IDENTITY, glm::vec3(m_scale, 1.0f))*/;
}