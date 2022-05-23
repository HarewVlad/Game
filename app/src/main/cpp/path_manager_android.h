struct PathManagerAndroid : public PathManager {
  void Initialize(AAssetManager *asset_manager);
  void GetTexture(Texture *texture, const char *path) override;
  void GetTextures(Texture *textures, int size, const char *fmt) override;
  int GetData(const char *path, void **data);

  AAssetManager *m_asset_manager;
};