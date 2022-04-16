void ControlSystem::Initialize(GLFWManager *glfw_manager) {
  m_glfw_manager = glfw_manager;
}

void ControlSystem::SetUpdateCallback(const std::function<void(Movement *, State *, float)> update) {
  m_update = update;
}