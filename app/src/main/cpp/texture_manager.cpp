bool TextureManager::Initialize() {
  stbi_set_flip_vertically_on_load(1);

  m_textures = NULL;

  return true;
}

bool TextureManager::Add(char *name, const char *filename) {
  Texture *texture = (Texture *)malloc(sizeof(Texture));

  unsigned char *buffer = stbi_load(filename, &texture->width, &texture->height, &texture->bpp, 4);
  if (!buffer) {
    LOG(LOG_ERROR, "TextureManager", "%s", "Unable to load texture");
    return false;
  }

  InitializeGraphics(texture, buffer);

  stbi_image_free(buffer);

  hmput(m_textures, name, texture);

  return true;
}

bool TextureManager::Add(char *name, void *data, int length) {
  Texture *texture = (Texture *)malloc(sizeof(Texture));

  unsigned char *buffer = stbi_load_from_memory((unsigned char *)data, length, &texture->width, &texture->height, &texture->bpp, 4);
  if (!buffer) {
    LOG(LOG_ERROR, "TextureManager", "%s", "Unable to load texture");
    free(texture);
    return false;
  }

  InitializeGraphics(texture, buffer);

  stbi_image_free(buffer);

  hmput(m_textures, name, texture);

  return true;
}

void TextureManager::Bind(char *name, unsigned int slot) {
  if (hmgeti(m_textures, name) >= 0) {
    unsigned int id = hmget(m_textures, name)->id;

    glCall(glActiveTexture(GL_TEXTURE0 + slot));
    glCall(glBindTexture(GL_TEXTURE_2D, id));
  }
}

void TextureManager::Unbind() {
  glCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void TextureManager::InitializeGraphics(Texture *texture, void *buffer) {
  glCall(glGenTextures(1, &texture->id));
  glCall(glBindTexture(GL_TEXTURE_2D, texture->id));

  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
  glCall(glBindTexture(GL_TEXTURE_2D, 0));
}
  
// TODO: Need to test this
void TextureManager::Shutdown() {
  Unbind();

  hmfree(m_textures);
}