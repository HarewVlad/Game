struct PathManager {
  virtual void GetTexture(Texture *texture, const char *path) = 0;
  virtual void GetTextures(Texture *textures, int size, const char *fmt) = 0;
};