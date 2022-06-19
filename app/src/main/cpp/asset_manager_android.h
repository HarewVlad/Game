struct AssetManagerAndroid : public AssetManager {
  void Initialize(AAssetManager *asset_manager);
  Texture GetTexture(const char *path) override;
  Texture *GetTextures(const char *fmt, int size) override;
  int GetData(const char *path, void **data);

  AAssetManager *m_asset_manager;
};