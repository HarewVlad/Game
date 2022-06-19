struct AssetManager {
  virtual Texture GetTexture(const char *path) = 0;
  virtual Texture *GetTextures(const char *fmt, int size) = 0;
};