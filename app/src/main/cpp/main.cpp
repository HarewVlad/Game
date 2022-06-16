#include "main.h"
#include "vendor/imgui/imgui.cpp"
#include "vendor/imgui/imgui_demo.cpp"
#include "vendor/imgui/imgui_draw.cpp"
#ifdef __ANDROID__
  #include "vendor/imgui/imgui_impl_android.cpp"
#elif defined _WIN32
  #include "vendor/imgui/imgui_impl_glfw.cpp"
#endif

#include "vendor/imgui/imgui_impl_opengl3.cpp"
#include "vendor/imgui/imgui_tables.cpp"
#include "vendor/imgui/imgui_widgets.cpp"

#include "log.cpp"
#include "utility.cpp"
#include "time.cpp"
#include "vertex_buffer_layout.cpp"
#include "vertex_buffer.cpp"
#include "index_buffer.cpp"
#include "vertex_array.cpp"
#include "box.cpp"
#ifdef __ANDROID__
  #include "window_manager_android.cpp"
  #include "egl_manager.cpp"
  #include "asset_manager_android.cpp"
#elif defined _WIN32
  #include "platform_manager_win32.cpp"
  #include "input_manager_win32.cpp"
  #include "asset_manager_win32.cpp"
#endif

#include "entity_manager.cpp"
#include "system.cpp"
#include "animation.cpp"
#include "renderer.cpp"
#include "shader.cpp"
#include "program.cpp"
#include "texture.cpp"
#include "position.cpp"
#include "body.cpp"
#include "movement.cpp"
#include "camera.cpp"
#include "effect_system.cpp"
#include "player_reset_system.cpp"
#include "enemy_reset_system.cpp"
#include "control_system.cpp"
#include "box_renderer.cpp"
#include "collision_system.cpp"
#include "movement_system.cpp"
#include "physics_system.cpp"
#include "animation_system.cpp"
#include "imgui_manager.cpp"
#include "interface_renderer.cpp"
#include "effect.cpp"

#ifdef __ANDROID__
  #include "imgui_manager_android.cpp"
#elif defined _WIN32
  #include "imgui_manager_win32.cpp"
#endif

#include "engine.cpp"

// #include "test.cpp"

// TODO: Link Program and VertexBufferLayout together i guess?
// TODO: Texture batching, instance drawing
// TODO: Generate background via shaders?
// TODO: Make position centered, based of size of an object? (Helps with radius issue)
// TODO: Add multithreading
// TODO: AOS to SOA?

void Check() {
  // Tests::Test();
}

#ifdef __ANDROID__
void android_main(struct android_app *app) {
#elif defined _WIN32
int main() {
#endif
  Check();

  srand(time(NULL));
#ifdef __ANDROID__
  // TODO: AndroidInitializer?
  EglManager egl_manager; // NOTE(Vlad): Initialization takes place in AndroidManager

  PlatformManagerAndroid platform_manager;
  platform_manager.Initialize(app, &egl_manager);

  while (Global_GameState != GameState::READY) {
    platform_manager.PollEvents();
  }

  ImGuiManagerAndroid imgui_manager;
  imgui_manager.Initialize((ANativeWindow *)platform_manager.m_window);

  PathManagerAndroid path_manager;
  path_manager.Initialize(app->activity->assetManager);
#elif defined _WIN32
  PlatformManagerWin32 platform_manager;
  platform_manager.Initialize(WINDOW_SIZE, TITLE);

  InputManagerWin32 input_manager;
  input_manager.Initialize((GLFWwindow *)platform_manager.m_window);

  ImGuiManagerWin32 imgui_manager;
  imgui_manager.Initialize((GLFWwindow *)platform_manager.m_window);

  AssetManagerWin32 asset_manager;
#endif
  // TODO: Rethink about Camera, Sound, other engine systems and how and where to initialize them
  Camera camera;
  camera.Initialize({0, 0});
  //

  Engine engine;
  engine.Initialize(&platform_manager, &asset_manager);

  // Systems
  PhysicsSystem physics_system;
  physics_system.Initialize(GRAVITY);

  ControlSystem control_system;
  control_system.Initialize(&input_manager);

  AnimationSystem animation_system;
  MovementSystem movement_system;
  CollisionSystem collision_system;
  PlayerResetSystem player_reset_system;
  EnemyResetSystem enemy_reset_system;
  EffectSystem effect_system;

  // Renderers
  BoxRenderer box_renderer; // NOTE(Vlad): Should be engine system?
  box_renderer.Initialize(&platform_manager.m_projection, &camera.m_view);

  InterfaceRenderer interface_renderer;
  interface_renderer.Initialize(&imgui_manager);

  engine.AddSystem<AnimationSystem>(&animation_system);
  engine.AddSystem<ControlSystem>(&control_system);
  engine.AddSystem<PhysicsSystem>(&physics_system);
  engine.AddSystem<MovementSystem>(&movement_system);
  engine.AddSystem<CollisionSystem>(&collision_system);
  engine.AddSystem<PlayerResetSystem>(&player_reset_system);
  engine.AddSystem<EnemyResetSystem>(&enemy_reset_system);
  engine.AddSystem<EffectSystem>(&effect_system);
  engine.AddRenderer<BoxRenderer>(&box_renderer);
  engine.AddRenderer<InterfaceRenderer>(&interface_renderer);

  engine.Script();
  engine.Loop();
}