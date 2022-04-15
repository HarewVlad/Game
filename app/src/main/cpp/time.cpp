void Time::Initialize() {
  m_base = timeGetTime();
}

// NOTE(Vlad): From Quake 2
int Time::GetMilliseconds() {
  return timeGetTime() - m_base;
}