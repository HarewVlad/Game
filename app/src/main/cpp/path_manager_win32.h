struct PathManagerWin32 : public PathManager {
  void GetTexture(Texture *texture, const char *path) override;
  void GetTextures(Texture *textures, int size, const char *fmt) override;
};