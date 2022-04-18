void ControlSystem::Initialize(GLFWManager *glfw_manager) {
  m_glfw_manager = glfw_manager;
}

void ControlSystem::SetUpdate(const std::function<void(int, float)> update) {
  m_update = update;
}