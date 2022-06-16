struct AssetManagerWin32 : public AssetManager {
  Texture GetTexture(const char *path) override;
  Texture *GetTextures(const char *fmt, int size) override;
};