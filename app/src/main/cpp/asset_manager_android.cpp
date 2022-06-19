void AssetManagerAndroid::Initialize(AAssetManager *asset_manager) {
  m_asset_manager = asset_manager;
}

int AssetManagerAndroid::GetData(const char *path, void **data) {
  int result = 0;

  AAsset *asset_descriptor =
      AAssetManager_open(m_asset_manager, path, AASSET_MODE_BUFFER);
  if (asset_descriptor) {
    result = AAsset_getLength(asset_descriptor);
    *data = (char *)malloc(result);
    int64_t num_bytes_read = AAsset_read(asset_descriptor, *data, result);
    AAsset_close(asset_descriptor);
    assert(num_bytes_read == result);
  }

  return result;
}

Texture AssetManagerAndroid::GetTexture(const char *path) {
  Texture result;

  void *data;
  int bytes = GetData(path, &data);

  result.Initialize(data, bytes);
  return result;
}

Texture *AssetManagerAndroid::GetTextures(const char *fmt, int size) {
  Texture *result = NULL;

  char buffer[256] = {};
  void *data;
  int bytes;
  for (int i = 0; i < size; ++i) {
    (void)snprintf(buffer, 256, fmt, i);

    bytes = GetData(buffer, &data);

    Texture texture;
    texture.Initialize(data, bytes);

    arrput(result, texture);
  }

  return result;
}