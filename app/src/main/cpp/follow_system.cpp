void FollowSystem::Initialize(GLFWManager *glfw_manager) {
  m_glfw_manager = glfw_manager;
}

void FollowSystem::Update(Position *a, Position *b) {
  // NOTE(Vlad): Follow to center of the object
  a->m_position.x = b->m_position.x - m_glfw_manager->m_width * 0.5f;
  a->m_position.y = b->m_position.y - m_glfw_manager->m_height * 0.5f;
}