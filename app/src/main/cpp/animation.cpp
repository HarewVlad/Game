bool Animation::Initialize() {
  m_textures = NULL;
  m_index = 0;
  m_time = 0.0f;

  return true;
}

void Animation::Add(Texture *textures, int size) {
  for (int i = 0; i < size; ++i) {
    arrput(m_textures, textures[i]);
  }
}

void Animation::Update(float dt) {
  if (m_time > 1.0f / arrlen(m_textures)) { // TODO: Delete this division later
    m_index = (m_index + 1) % arrlen(m_textures);
    m_time = 0.0f;
  } else {
    m_time += dt;
  }
}

Texture *Animation::GetCurrentTexture() {
  return &m_textures[m_index];
}