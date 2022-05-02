void Animation::Initialize() {
  m_animation_map = NULL;
  m_index = 0;
  m_id = 0;
  m_time = 0.0f;
}

void Animation::Add(int id, AnimationRange animation_range) {
  hmput(m_animation_map, id, animation_range);
}

inline void Animation::SetAnimation(int id) {
  if (m_id != id) {
    m_id = id;
    m_time = 0;
  }
}

void Animation::Update(float dt) {
  AnimationRange range = hmget(m_animation_map, m_id);
  int size = range.m_end - range.m_start;
  if (m_time > 1.0f / size) {
    m_index = (m_index + 1) % size;
    m_time = 0.0f;
  } else {
    m_time += dt;
  }
}

int Animation::GetIndex() {
  AnimationRange range = hmget(m_animation_map, m_id);

  return m_index + range.m_start;
}