void PathManagerWin32::GetTexture(Texture *texture, const char *path) {
  char buffer[256] = {};
  strcat(buffer, ASSETS_PATH);
  strcat(buffer, path);

  texture->Initialize(buffer);
}

void PathManagerWin32::GetTextures(Texture *textures, int size, const char *fmt) {
  char buffer[256] = {};
  strcat(buffer, ASSETS_PATH);
  strcat(buffer, fmt);
  
  for (int i = 0; i < size; ++i) {
    char path[256];
    (void)snprintf(path, 256, buffer, i);

    textures[i].Initialize(path);
  }
}