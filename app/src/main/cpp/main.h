#define STB_IMAGE_IMPLEMENTATION
#define STB_DS_IMPLEMENTATION
#define GLEW_STATIC

// TODO: Rethink place to zero-initialize members of structs

// C++
#include <iostream>
#include <functional>
#include <unordered_map>
///

// C
#include <stdlib.h>
///

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
#include "stb/stb_image.h"
#include "stb/stb_ds.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

static bool Global_IsInitialized = false;
static const glm::mat4 Global_Identity = glm::mat4(1.0f);
static const int MAX_FPS = 60;
static const int MIN_ALLOCATION_SIZE = 100;

enum class GameState {
  MENU,
  RUN,
  // NOTE(Vlad): Insert your states
  EXIT
};

static GameState Global_GameState = GameState::MENU;

#include "log.h"
#include "utility.h"
#include "time.h"
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
#include "state.h"
#include "shader.h"
#include "program.h"
#include "texture.h"
#include "animation.h"
#include "position.h"
#include "follow_system.h"
#include "body.h"
#include "movement.h"
#include "camera_system.h"
#include "control_system.h"
#include "health.h"
#include "renderer_system.h"
#include "collision_system.h"
#include "physics_system.h"
#include "imgui_manager.h"
#include "interface_system.h"
#include "entity_manager.h"
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
#pragma comment(lib, "Winmm.lib")