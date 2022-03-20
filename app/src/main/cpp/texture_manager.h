// TODO: Create TextureGroup (Forest, House, ...) and store it in m_textures
// TODO: Add glDeleteTextures(1, &m_id);
// TODO: (VERY IMPORTANT) Make TextureManager

struct Texture {
  unsigned int id;
  int width;
  int height;
  int bpp;
};

struct TextureMap {
  char *key;
  Texture *value;
};

struct TextureManager {
  bool Initialize();
  bool Add(char *name, const char *filename);
  bool Add(char *name, void *data, int length);
  void Bind(char *name, unsigned int slot = 0);
  void Unbind();
  void Shutdown();

  void InitializeGraphics(Texture *texture, void *buffer);

  TextureMap *m_textures;
};