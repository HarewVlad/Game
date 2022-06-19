void Effect::Initialize(float duration, float frequency) {
  m_time = 0;
  m_total_time = duration;
  m_frequency = frequency;
  m_duration = duration;
}

bool Effect::IsExecuting() const {
  return m_total_time < m_duration;
}

void Effect::Start() {
  m_total_time = 0;
}

void Effect::Stop() {
  m_total_time = m_duration;
}