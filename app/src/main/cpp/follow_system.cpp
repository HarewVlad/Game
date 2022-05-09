void FollowSystem::Initialize(GLFWManager *glfw_manager) {
  m_glfw_manager = glfw_manager;
}

void FollowSystem::Update(Position *a, Position *b) {
  a->m_xy.x = b->m_xy.x - m_glfw_manager->m_width * 0.5f;
  a->m_xy.y = b->m_xy.y - m_glfw_manager->m_height * 0.5f;
}

void FollowSystem::Update(glm::vec2 &a, Position *b) {
  a.x = b->m_xy.x - m_glfw_manager->m_width * 0.5f;
  a.y = b->m_xy.y - m_glfw_manager->m_height * 0.5f;
}