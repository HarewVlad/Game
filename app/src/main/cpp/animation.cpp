void Animation::Set(int type) {
  if (m_type != type) {
    m_type = type;
    m_time = 0;
    m_index = 0;
  }
}