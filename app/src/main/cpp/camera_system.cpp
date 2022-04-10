bool CameraSystem::Initialize(GLFWManager *glfw_manager) {
  m_position = {0, 0};
  m_view = glm::mat4(1.0f);
  m_glfw_manager = glfw_manager;

  return true;
}

glm::mat4 CameraSystem::GetView() {
  return glm::lookAt(glm::vec3(m_position, 0), glm::vec3(m_position, -1),
                       glm::vec3(0, 1, 0));
}

void CameraSystem::Follow(Position *position) {
  glm::vec2 window_size = {m_glfw_manager->m_width, m_glfw_manager->m_height};
  m_position = position->m_position - window_size * 0.5f;
}