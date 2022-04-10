bool Animation::Initialize() {
  m_textures = NULL;
  m_index = 0;
  m_id = 0;
  m_time = 0.0f;

  return true;
}

void Animation::Add(int id, Texture *textures) {
  hmput(m_textures, id, textures);
}

void Animation::Update(float dt) {
  Texture *textures = hmget(m_textures, m_id); // TODO: Remove later
  if (m_time > 1.0f / arrlen(textures)) {
    m_index = (m_index + 1) % arrlen(textures);
    m_time = 0.0f;
  } else {
    m_time += dt;
  }
}

Texture *Animation::GetCurrentTexture() {
  Texture *textures = hmget(m_textures, m_id);
  return &textures[m_index];
}

void Animation::SetId(int id) {
  if (m_id != id) {
    m_id = id;
    m_index = 0;
  }
}