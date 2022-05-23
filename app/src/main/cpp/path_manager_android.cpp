void PathManagerAndroid::Initialize(AAssetManager *asset_manager) {
  m_asset_manager = asset_manager;
}

int PathManagerAndroid::GetData(const char *path, void **data) {
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

void PathManagerAndroid::GetTexture(Texture *texture, const char *path) {
  void *data;
  int bytes = GetData(path, &data);

  texture->Initialize(data, bytes);
}

void PathManagerAndroid::GetTextures(Texture *textures, int size, const char *fmt) {
  char buffer[256] = {};
  void *data;
  int bytes;
  for (int i = 0; i < size; ++i) {
    (void)snprintf(buffer, 256, fmt, i);

    bytes = GetData(buffer, &data);

    textures[i].Initialize(data, bytes);
  }
}