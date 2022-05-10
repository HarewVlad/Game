#include "main.h"
#include "imgui/imgui.cpp"
#include "imgui/imgui_demo.cpp"
#include "imgui/imgui_draw.cpp"
#ifdef __ANDROID__
  #include "imgui/imgui_impl_android.cpp"
#elif defined _WIN32
  #include "imgui/imgui_impl_glfw.cpp"
#endif

#include "imgui/imgui_impl_opengl3.cpp"
#include "imgui/imgui_tables.cpp"
#include "imgui/imgui_widgets.cpp"

#include "log.cpp"
#include "utility.cpp"
#include "time.cpp"
#include "size.cpp"
#include "vertex_buffer_layout.cpp"
#include "vertex_buffer.cpp"
#include "index_buffer.cpp"
#include "vertex_array.cpp"
#include "box.cpp"
#ifdef __ANDROID__
  #include "android_manager.cpp"
  #include "egl_manager.cpp"
#elif defined _WIN32
  #include "glfw_manager.cpp"
#endif

#include "state.cpp"
#include "shader.cpp"
#include "program.cpp"
#include "texture.cpp"
#include "animation.cpp"
#include "position.cpp"
#include "follow_system.cpp"
#include "body.cpp"
#include "movement.cpp"
#include "camera_system.cpp"
#include "control_system.cpp"
#include "health.cpp"
#include "renderer_system.cpp"
#include "collision_system.cpp"
#include "physics_system.cpp"
#include "imgui_manager.cpp"
#include "interface_system.cpp"
#include "score.cpp"
#include "effects/effect_blink.cpp"
#include "entity_manager.cpp"
#ifdef __ANDROID__
  #include "imgui_manager_android.cpp"
#elif defined _WIN32
  #include "imgui_manager_win32.cpp"
#endif

#include "engine.cpp"

void Initialize() {
  srand(timeGetTime());
  // stbds_rand_seed(timeGetTime());
}

// TODO: Rework code, make initialization the same for two platforms
// TODO: Link Program and VertexBufferLayout together i guess?
// TODO: Instead of return codes, just make and assertion and terminate the programm if error is hard
// TODO: Texture batching, instance drawing
// TODO: Generate background via shaders?
// TODO: Copy IndexBuffer and VertexArray to Box?
// TODO: To minimize performance overhead, bind callbacks to entity ids?
// TODO: Add ability to add custom systems
// TODO: Make position centered, based of size of an object? (Helps with radius issue)

#ifdef __ANDROID__
void android_main(struct android_app *app) {
#elif defined _WIN32
int main() {
  Engine engine;
  engine.Initialize();
  engine.Start();

  ExitProcess(0); // TODO: Replace with android analouge?
}

#endif