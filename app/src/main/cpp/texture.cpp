// TODO: Remove returns and place asserts
bool Texture::Initialize(void *data, int length) {
  stbi_set_flip_vertically_on_load(1);

  unsigned char *buffer = stbi_load_from_memory((unsigned char *)data, length, &m_width, &m_height, &m_bpp, 4);
  if (!buffer) {
    LOG(LOG_ERROR, "Texture", "%s", "Unable to load texture");
    return false;
  }

  InitializeGraphics(buffer);

  stbi_image_free(buffer);

  return true;
}

// TODO: Remove returns and place asserts
bool Texture::Initialize(const char *filename) {
  stbi_set_flip_vertically_on_load(1);

  unsigned char *buffer = stbi_load(filename, &m_width, &m_height, &m_bpp, 4);
  if (!buffer) {
    LOG(LOG_ERROR, "Texture", "%s", "Unable to load texture");
    return false;
  }

  InitializeGraphics(buffer);

  stbi_image_free(buffer);

  return true;
}

void Texture::InitializeGraphics(void *buffer) {
  glCall(glGenTextures(1, &m_id));
  glCall(glBindTexture(GL_TEXTURE_2D, m_id));

  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
  glCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::Bind(unsigned int slot) {
  glCall(glActiveTexture(GL_TEXTURE0 + slot));
  glCall(glBindTexture(GL_TEXTURE_2D, m_id));
}

void Texture::Unbind() {
  glCall(glBindTexture(GL_TEXTURE_2D, 0));
}