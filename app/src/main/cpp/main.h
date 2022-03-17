#define STB_IMAGE_IMPLEMENTATION
#define GLEW_STATIC

#ifdef __ANDROID__
  #include <android/log.h>
  #include <android_native_app_glue.h>
  #include <android/asset_manager.h>
  #include <EGL/egl.h>
  #include <GLES3/gl3.h>
#elif defined _WIN32
  #include "Windows.h"
  #include "GL\glew.h"
  #include "GLFW\glfw3.h"
#endif

#include "imgui/imgui.h"
#ifdef __ANDROID__
  #include "imgui/imgui_impl_android.h"
#elif defined _WIN32
  #include "imgui/imgui_impl_glfw.h"
#endif
#include "imgui/imgui_impl_opengl3.h"
#include "stb_image/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

// TODO: Replace all this shit by "stb_ds.h"
#include <unordered_map>
#include <string>
#include <vector>
//

static bool Global_IsInitialized = false;

#include "log.h"
#include "utility.h"
#ifdef __ANDROID__
  #include "egl_manager.h"
#elif defined _WIN32
  #include "glfw_manager.h"
#endif
#include "vertex_buffer_layout.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "box.h"
#include "shader.h"
#include "program.h"
#include "texture.h"
#include "background.h"
#include "game.h"
#include "imgui_manager.h"
#ifdef __ANDROID__
  #include "imgui_manager_android.h"
  #include "android_manager.h"
#elif defined _WIN32
  #include "imgui_manager_win32.h"
  #include "win32_manager.h"
#endif

#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "libs\\glfw3.lib")
#pragma comment(lib, "libs\\glew32s.lib")