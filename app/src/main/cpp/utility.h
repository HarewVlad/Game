// TODO: Remove OpenGL from Utility
// TOOD: Make like OpenGL, Android, Utility

namespace Game {
  const glm::vec2 GetEnemyPosition(const glm::vec2& size) {
    return glm::vec2(1 + rand() % (int)size.x, size.y * 0.8f + rand() % (int)size.y * 0.9f);
  }
}

namespace Utility {
  void Wait(int milliseconds);
  void LinkPath(char *result, const char *a, const char *b);

namespace OpenGL {
// #define ASSERT(x) if (!(x)) __debugbreak();

#define glCall(x) \
  x;              \
  Utility::OpenGL::glHandleError(#x, __FILE__, __LINE__);

static bool glHandleError(const char *function, const char *file, int line);
static unsigned int GetTypeSize(unsigned int type);
}

#ifdef __ANDROID__
  static int ShowSoftKeyboardInput(struct android_app *app);
#endif
} // namespace Utility