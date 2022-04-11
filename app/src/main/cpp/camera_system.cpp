bool CameraSystem::Initialize(GLFWManager *glfw_manager, Position *position) {
  m_view = glm::mat4(1.0f);
  m_glfw_manager = glfw_manager;
  m_position = position;

  return true;
}

glm::mat4 CameraSystem::GetView() {
  return glm::lookAt(glm::vec3(m_position->m_position, 0), glm::vec3(m_position->m_position, -1),
                       glm::vec3(0, 1, 0));
}

void CameraSystem::Follow(Position *position) {
  m_position->m_position.x = position->m_position.x - m_glfw_manager->m_width * 0.5f;
  m_position->m_position.y = position->m_position.y - m_glfw_manager->m_height * 0.5f;
}