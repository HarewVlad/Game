void CameraSystem::Initialize(Position *position) {
  m_view = IDENTITY;
  m_position = position;
}

inline glm::mat4 CameraSystem::GetView() const {
  return glm::lookAt(glm::vec3(m_position->m_xy, 0), glm::vec3(m_position->m_xy, -1),
                       glm::vec3(0, 1, 0));
}