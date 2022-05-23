void FollowSystem::Initialize(WindowManager *window_manager) {
  m_window_manager = window_manager;
}

void FollowSystem::Update(Position *a, Position *b) {
  const glm::vec2 window_size = m_window_manager->m_size;

  a->m_xy.x = b->m_xy.x - window_size.x * 0.5f;
  a->m_xy.y = b->m_xy.y - window_size.y * 0.5f;
}

void FollowSystem::Update(glm::vec2 &a, Position *b) {
  const glm::vec2 window_size = m_window_manager->m_size;

  a.x = b->m_xy.x - window_size.x * 0.5f;
  a.y = b->m_xy.y - window_size.y * 0.5f;
}