struct AssetManagerAndroid : public AssetManager {
  void Initialize(AAssetManager *asset_manager);
  Texture GetTexture(const char *path) override;
  void GetTextures(Texture *textures, int size, const char *fmt) override;
  int GetData(const char *path, void **data);

  AAssetManager *m_asset_manager;
};