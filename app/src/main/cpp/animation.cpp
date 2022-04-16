void Animation::Initialize() {
  m_textures = NULL;
  m_index = 0;
  m_id = 0;
  m_time = 0.0f;
}

void Animation::Add(int id, Texture *textures) {
  hmput(m_textures, id, textures);
}

void Animation::Update(State *state, float dt) {
  if (m_id != state->m_value) { // NOTE(Vlad): Mb just use SetId method instead of this (State)?
    m_id = state->m_value;
    m_index = 0;
  }

  Texture *textures = hmget(m_textures, m_id);
  if (m_time > 1.0f / arrlen(textures)) {
    m_index = (m_index + 1) % arrlen(textures);
    m_time = 0.0f;
  } else {
    m_time += dt;
  }
}

void Animation::Update(float dt) { // NOTE(Vlad): In case when animation doesn't have any state
  Texture *textures = hmget(m_textures, m_id);
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