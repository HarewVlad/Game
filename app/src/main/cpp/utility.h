// TODO: Remove OpenGL from Utility
namespace Utility {
namespace OpenGL {
// #define ASSERT(x) if (!(x)) __debugbreak();

#define glCall(x) \
  x;              \
  Utility::OpenGL::glHandleError(#x, __FILE__, __LINE__);

static bool glHandleError(const char *function, const char *file, int line);
static unsigned int GetTypeSize(unsigned int type);
}

#ifdef __ANDROID__
  static int GetAssetData(AAssetManager *asset_manager, const char* filename, void** data);
  static int ShowSoftKeyboardInput(struct android_app *app);
#endif
} // namespace Utility