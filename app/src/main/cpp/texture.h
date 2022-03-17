// TODO: Create TextureGroup (Forest, House, ...) and store it in m_textures
// TODO: Add glDeleteTextures(1, &m_id);

struct Texture {
  Texture();
  bool Initialize(void *data, int length);
  void Bind();
  void Unbind();

  unsigned int m_id;
  int m_width;
  int m_height;
  int m_bpp;
};