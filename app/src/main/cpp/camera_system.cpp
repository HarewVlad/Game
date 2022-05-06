void CameraSystem::Initialize(GLFWManager *glfw_manager, Position *position) {
  m_view = IDENTITY;
  m_glfw_manager = glfw_manager;
  m_position = position;
}

inline glm::mat4 CameraSystem::GetView() const {
  return glm::lookAt(glm::vec3(m_position->m_position, 0), glm::vec3(m_position->m_position, -1),
                       glm::vec3(0, 1, 0));
}