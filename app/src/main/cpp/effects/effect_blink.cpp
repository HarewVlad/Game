void EffectBlink::Initialize(float duration, float frequency) {
  m_time = 0;
  m_total_time = duration;
  m_frequency = frequency;
  m_duration = duration;
}

bool EffectBlink::IsExecuting() const {
  return m_total_time < m_duration;
}

void EffectBlink::Start() {
  m_total_time = 0;
}

void EffectBlink::Stop() {
  m_total_time = m_duration;
}

void EffectBlink::Update(int *blink, float dt) {
  if (m_total_time < m_duration) {
    if (m_time > 1 / m_frequency) {
      *blink ^= 1;
      m_time = 0;
    } else {
      m_time += dt;
      m_total_time += dt;
    }
  } else {
    *blink = 1;
  }
}