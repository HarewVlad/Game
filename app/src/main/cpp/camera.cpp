void Camera::Initialize(const glm::vec2& xy) {
  m_xy = xy;
  m_view = glm::lookAt(glm::vec3(xy, 0), glm::vec3(xy, -1),
                       glm::vec3(0, 1, 0));
}