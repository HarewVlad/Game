bool Camera::Initialize() {
  m_position = {0, 0};
  m_velocity = {0, 0};
  m_target = {0, 0};
  m_view = glm::mat4(1.0f);

  return true;
}

void Camera::Update(float dt) {
  m_position += m_velocity * dt;
  m_target += m_velocity * dt;

  m_velocity -= m_velocity * dt;

  // TOOD: Update m_view only when something above is changed
  m_view = glm::lookAt(glm::vec3(m_position, 0), glm::vec3(m_target, -1),
                       glm::vec3(0, 1, 0));
}