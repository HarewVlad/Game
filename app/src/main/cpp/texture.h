// TODO: Create TextureGroup (Forest, House, ...) and store it in m_textures
// TODO: Add glDeleteTextures(1, &m_id);
// TODO: (VERY IMPORTANT) Make TextureManager

struct Texture {
  bool Initialize(void *data, int length);
  bool Initialize(const char *filename);
  void InitializeGraphics(void *buffer);
  void Bind(unsigned int slot = 0);
  void Unbind();

  unsigned int m_id;
  int m_width;
  int m_height;
  int m_bpp;
};

struct TextureMap {
  int key;
  Texture *value;
};

struct TextureArrayMap {
  int key;
  Texture **value;
};