// TODO: Remove OpenGL from Utility
// TOOD: Make like OpenGL, Android, Utility
namespace Utility {
  void Wait(int milliseconds);

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