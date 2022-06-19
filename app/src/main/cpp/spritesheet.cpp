void Spritesheet::Initialize(const glm::vec2 &size) {
  m_size = size;
}

void Spritesheet::Add(int id, int count) {
  hmput(m_textures, id, count);
}

const glm::vec2 Spritesheet::Offset(int id, int index) {
  int count = hmget(m_textures, id);

  return {m_size.x * index, m_size.y * id};
}