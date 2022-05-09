void FollowSystem::Initialize(WindowSize *window_size) {
  m_window_size = window_size;
}

void FollowSystem::Update(Position *a, Position *b) {
  a->m_xy.x = b->m_xy.x - m_window_size->m_width * 0.5f;
  a->m_xy.y = b->m_xy.y - m_window_size->m_height * 0.5f;
}

void FollowSystem::Update(glm::vec2 &a, Position *b) {
  a.x = b->m_xy.x - m_window_size->m_width * 0.5f;
  a.y = b->m_xy.y - m_window_size->m_height * 0.5f;
}