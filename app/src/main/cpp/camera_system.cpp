void CameraSystem::Initialize(const glm::vec2& xy) {
  m_view = IDENTITY;
  m_xy = xy;
}

inline glm::mat4 CameraSystem::GetView() const {
  return glm::lookAt(glm::vec3(m_xy, 0), glm::vec3(m_xy, -1),
                       glm::vec3(0, 1, 0));
}