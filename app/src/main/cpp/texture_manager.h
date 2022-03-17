// TODO: Create TextureGroup (Forest, House, ...) and store it in m_textures
// TODO: Add glDeleteTextures(1, &m_id);
// TODO: (VERY IMPORTANT) Make TextureManager

struct Texture {
  unsigned int id;
  int width;
  int height;
  int bpp;
};

struct TextureManager {
  bool Initialize();
  bool Add(const char *name, const char *filename);
  bool Add(const char *name, void *data, int length);
  void Bind(const char *name);
  void Unbind();

  void InitializeGraphics(Texture *texture, void *buffer);
  
  std::unordered_map<std::string, Texture *> m_textures;
};