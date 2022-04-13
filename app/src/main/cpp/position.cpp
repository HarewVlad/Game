void Position::Initialize(const glm::vec2& position) {
  m_position = position;
}

void Position::MoveX(float x) {
  m_position.x += x;
}

void Position::MoveY(float y) {
  m_position.y += y;
}

glm::mat4 Position::GetModel() {
  return glm::translate(Global_Identity, glm::vec3(m_position, 0));
  // TODO: Add rotation and so on ...
}