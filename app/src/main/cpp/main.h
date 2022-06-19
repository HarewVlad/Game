#define STB_IMAGE_IMPLEMENTATION
#define STB_DS_IMPLEMENTATION
#define GLEW_STATIC
#ifdef _WIN32
  #define IMGUI_IMPL_OPENGL_LOADER_GLEW
#endif

// C++
#include <iostream>
#include <functional>
#include <thread>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
///

// C
#include <stdlib.h>
#include <assert.h>
///

#ifdef __ANDROID__
  #include <unistd.h>
  #include <android/log.h>
  #include <android_native_app_glue.h>
  #include <android/asset_manager.h>
  #include <EGL/egl.h>
  #include <GLES3/gl3.h>
#elif defined _WIN32
  #include "Windows.h"
  #include "vendor/gl/glew.h"
  #include "vendor/glfw/glfw3.h"
#endif

#include "vendor/imgui/imgui.h"
#ifdef __ANDROID__
  #include "vendor/imgui/imgui_impl_android.h"
#elif defined _WIN32
  #include "vendor/imgui/imgui_impl_glfw.h"
#endif
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "vendor/stb/stb_image.h"
#include "vendor/stb/stb_ds.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtx/transform.hpp"
#include "vendor/glm/ext/matrix_clip_space.hpp"

#include "config.h"

enum GameState {
  GameState_None = 0,
  GameState_Ready = 1 << 0,
  GameState_Menu = 1 << 1,
  GameState_Run = 1 << 2,
  GameState_PlayerReset = 1 << 3,
  GameState_EnemyReset = 1 << 4,
  GameState_Reset = GameState_PlayerReset | GameState_EnemyReset,
  GameState_GameOver = 1 << 4,
  GameState_Exit = 1 << 5
};

static int Global_GameState = GameState_None;

#include "log.h"
#include "utility.h"
#include "time.h"
#include "range.h"
#include "input_manager.h"
#include "platform_manager.h"
#include "texture.h"
#include "asset_manager.h"
#ifdef __ANDROID__
  #include "egl_manager.h"
  #include "asset_manager_android.h"
#elif defined _WIN32
  #include "platform_manager_win32.h"
  #include "input_manager_win32.h"
  #include "asset_manager_win32.h"
#endif

#include "entity_manager.h"
#include "animation_type.h"
#include "spritesheet.h"
#include "system.h"
#include "renderer.h"
#include "vertex_buffer_layout.h"
#include "buffer.h"
#include "vertex_array.h"
#include "box.h"
#include "shader.h"
#include "program.h"
#include "stamina.h"
#include "animation.h"
#include "position.h"
#include "body.h"
#include "movement.h"
#include "camera.h"
#include "effect_system.h"
#include "player_reset_system.h"
#include "enemy_reset_system.h"
#include "control_system.h"
#include "health.h"
#include "box_renderer.h"
#include "collision_system.h"
#include "movement_system.h"
#include "physics_system.h"
#include "animation_system.h"
#include "imgui_manager.h"
#include "interface_renderer.h"
#include "score.h"
#include "effect.h"
#ifdef __ANDROID__
  #include "imgui_manager_android.h"
  #include "window_manager_android.h"
#elif defined _WIN32
  #include "imgui_manager_win32.h"
#endif

#include "engine.h"

#ifdef _WIN32
  #pragma comment(lib, "Shell32.lib")
  #pragma comment(lib, "User32.lib")
  #pragma comment(lib, "Gdi32.lib")
  #pragma comment(lib, "opengl32.lib")
  #pragma comment(lib, "libs\\glfw3.lib")
  #pragma comment(lib, "libs\\glew32s.lib")
  #pragma comment(lib, "Winmm.lib")
#endif