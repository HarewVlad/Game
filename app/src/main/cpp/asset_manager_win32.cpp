Texture AssetManagerWin32::GetTexture(const char *path) {
  Texture result = {};

  // TODO: Make a function
  char buffer[256] = {};
  Utility::LinkPath(&buffer[0], ASSETS_PATH, path);

  result.Initialize(buffer);
  return result;
}

Texture *AssetManagerWin32::GetTextures(const char *fmt, int size) {
  Texture *result = NULL;

  char buffer[256] = {};
  Utility::LinkPath(&buffer[0], ASSETS_PATH, fmt);
  
  for (int i = 0; i < size; ++i) {
    char path[256];
    (void)snprintf(path, 256, buffer, i);

    Texture texture;
    texture.Initialize(path);

    arrput(result, texture);
  }

  return result;
}