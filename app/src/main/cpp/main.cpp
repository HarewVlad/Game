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
#include "vertex_buffer_layout.cpp"
#include "vertex_buffer.cpp"
#include "index_buffer.cpp"
#include "vertex_array.cpp"
#include "box.cpp"

#ifdef __ANDROID__
  #include "android_manager.cpp"
  #include "egl_manager.cpp"
#elif defined _WIN32
  #include "win32_manager.cpp"
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
#include "entity_manager.cpp"
#ifdef __ANDROID__
  #include "imgui_manager_android.cpp"
#elif defined _WIN32
  #include "imgui_manager_win32.cpp"
#endif

void Initialize() {
  srand(timeGetTime());
  stbds_rand_seed(timeGetTime());
}

// TODO: Rework code, make initialization the same for two platforms
// TODO: Link Program and VertexBufferLayout together i guess?
// TODO: Instead of return codes, just make and assertion and terminate the programm if error is hard
// TODO: Texture batching, instance drawing

#ifdef __ANDROID__
void android_main(struct android_app *app) {
  EglManager egl_manager;     // Initialization in "android_manager"
  ImGuiManager imgui_manager; // Initialization in "android_manager"
  Game game; // Initialization in "android_manager"

  AndroidManager android_manager;
  {
    android_manager.Initialize(app, &egl_manager, &imgui_manager, &game);
    android_manager.Run(app);
  }
}
#elif defined _WIN32

int main() {
  Initialize();

  GLFWManager glfw_manager;
  if (!glfw_manager.Initialize(1920, 1080, "Game")) {
    return -1;
  }

  ImGuiManagerWin32 imgui_manager;
  imgui_manager.Initialize(glfw_manager.m_window);

  Shader vertex_shader;
  {
    const char *vertex_shader_code = R"(#version 330 core
                                     layout(location = 0) in vec4 position;
                                     layout(location = 1) in vec2 tex;

                                     out vec2 v_Tex;

                                     uniform mat4 u_MVP;

                                     void main() {
                                     gl_Position = u_MVP * position;
                                     v_Tex = tex;
                                     })";
    vertex_shader.Initialize(vertex_shader_code, GL_VERTEX_SHADER);
  }

  Shader fragment_shader;
  {
    const char *fragment_shader_code = R"(#version 330 core
        precision mediump float;
        layout(location = 0) out vec4 color;

        in vec2 v_Tex;

        uniform sampler2D u_Texture;

        void main() {
        vec4 texCoord = texture(u_Texture, v_Tex);
        color = texCoord;
        })";
    fragment_shader.Initialize(fragment_shader_code, GL_FRAGMENT_SHADER);
  }

  Program program;
  {
    program.Initialize();
    program.AddShader(&vertex_shader);
    program.AddShader(&fragment_shader);
    program.Link();
  }

  IndexBuffer index_buffer;
  index_buffer.Initialize();

  VertexBufferLayout vertex_buffer_layout;
  vertex_buffer_layout.Initialize();

  // Systems
  Position camera_position;
  camera_position.Initialize({0, 0});

  CameraSystem camera_system;
  camera_system.Initialize(&glfw_manager, &camera_position);

  RendererSystem renderer_system;
  renderer_system.Initialize(&glfw_manager);

  PhysicsSystem physics_system;
  physics_system.Initialize({0, -18.8f});

  CollisionSystem collision_system;
  collision_system.Initialize();

  FollowSystem follow_system;
  follow_system.Initialize(&glfw_manager);

  ControlSystem control_system;

  InterfaceSystem interface_system;
  interface_system.Initialize(&imgui_manager);

  EntityManager entity_manager;
  entity_manager.Initialize(&camera_system, &renderer_system, &physics_system, &collision_system, &follow_system, &control_system, &interface_system);

  // Background
  Texture background_texture;
  background_texture.Initialize("..\\assets\\background.png");

  Box background_box;
  VertexArray background_vertex_array;
  float background_width = glfw_manager.m_width;
  float background_height = glfw_manager.m_height;
  {
    VertexBuffer vertex_buffer;
    vertex_buffer.Initialize(background_width, background_height);

    // Vertex buffer layout
    vertex_buffer_layout.Push(GL_FLOAT, 2);
    vertex_buffer_layout.Push(GL_FLOAT, 2);

    // Vertex array
    background_vertex_array.Initialize();
    background_vertex_array.AddBuffer(&vertex_buffer, &vertex_buffer_layout);

    background_box.Initialize(&index_buffer, &background_vertex_array);
  }

  Position background_position;
  background_position.Initialize({0, 0});

  entity_manager.AddBox(0, background_box);
  entity_manager.AddTexture(0, background_texture);
  entity_manager.AddProgram(0, program);
  entity_manager.AddPosition(0, background_position);
  entity_manager.AddToRenderer(0, ImageType::TEXTURE);

  // Player
  enum class PlayerState {
    IDLE,
    RUN
  };

  State player_state;
  player_state.Initialize((int)PlayerState::IDLE);

  Texture *player_idle = NULL;
  arrsetlen(player_idle, 4);
  char buffer[128];
  for (int i = 0; i < arrlen(player_idle); ++i) {
    (void)snprintf(buffer, 128, "..\\assets\\player\\idle\\%d.png", i);
    player_idle[i].Initialize(buffer);
  }

  Texture *player_run = NULL;
  arrsetlen(player_run, 8);
  for (int i = 0; i < arrlen(player_run); ++i) {
    (void)snprintf(buffer, 128, "..\\assets\\player\\run\\%d.png", i);
    player_run[i].Initialize(buffer);
  }

  Animation player_animation;
  player_animation.Initialize();
  player_animation.Add((int)PlayerState::IDLE, player_idle);
  player_animation.Add((int)PlayerState::RUN, player_run);

  Box player_box;
  VertexBuffer player_vertex_buffer;
  VertexArray player_vertex_array;
  float player_width = player_idle[0].m_width;
  float player_height = player_idle[0].m_height;

  float player_vertices[] = {0, 0, 0.0f, 0.0f,
                         0, player_height,  0.0f, 1.0f,
                         player_width,  player_height,  1.0f, 1.0f,
                         player_width,  0, 1.0f, 0.0f};

  float player_vertices_flipped[] = {0, 0, 1.0f, 0.0f,
                     0, player_height,  1.0f, 1.0f,
                     player_width,  player_height,  0.0f, 1.0f,
                     player_width,  0, 0.0f, 0.0f};

  {
    player_vertex_buffer.Initialize(player_width, player_height);

    player_vertex_array.Initialize();
    player_vertex_array.AddBuffer(&player_vertex_buffer, &vertex_buffer_layout);

    player_box.Initialize(&index_buffer, &player_vertex_array);
  }

  Position player_position;
  player_position.Initialize({glfw_manager.m_width * 0.5f, 80});

  Movement player_movement;
  player_movement.Initialize({10, 0}, {10, 0}, 1.0f, 0);

  Body player_body;
  player_body.Initialize(BodyType::NORMAL, {player_width, player_height});

  Health player_health;
  player_health.Initialize(3);

  entity_manager.AddBox(1, player_box);
  entity_manager.AddAnimation(1, player_animation);
  entity_manager.AddProgram(1, program);
  entity_manager.AddPosition(1, player_position);
  entity_manager.AddMovement(1, player_movement);
  entity_manager.AddBody(1, player_body);
  entity_manager.AddState(1, player_state);
  entity_manager.AddHealth(1, player_health);
  entity_manager.AddToRenderer(1, ImageType::ANIMATION);
  entity_manager.SetToControl(1);
  entity_manager.SetToInterface(1);

  // Arena
  int arena_width = glfw_manager.m_width;
  int arena_height = glfw_manager.m_height * 1.5f;

  // Bear, Bandit, Golem
  const int enemies_count = 10000;
  const int enemy_types = 4;

  Texture *enemy_run_textures[enemy_types] = {};

  arrsetlen(enemy_run_textures[0], 4);
  for (int i = 0; i < arrlen(enemy_run_textures[0]); ++i) {
    (void)snprintf(buffer, 128, "..\\assets\\bear\\%d.png", i);
    enemy_run_textures[0][i].Initialize(buffer);
  }

  arrsetlen(enemy_run_textures[1], 4);
  for (int i = 0; i < arrlen(enemy_run_textures[1]); ++i) {
    (void)snprintf(buffer, 128, "..\\assets\\bandit\\%d.png", i);
    enemy_run_textures[1][i].Initialize(buffer);
  }

  arrsetlen(enemy_run_textures[2], 6);
  for (int i = 0; i < arrlen(enemy_run_textures[2]); ++i) {
    (void)snprintf(buffer, 128, "..\\assets\\golem\\%d.png", i);
    enemy_run_textures[2][i].Initialize(buffer);
  }

  arrsetlen(enemy_run_textures[3], 4);
  for (int i = 0; i < arrlen(enemy_run_textures[3]); ++i) {
    (void)snprintf(buffer, 128, "..\\assets\\ent\\%d.png", i);
    enemy_run_textures[3][i].Initialize(buffer);
  }

  Animation enemy_animations[enemies_count];
  for (int i = 0; i < _countof(enemy_animations); ++i) {
    enemy_animations[i].Initialize();
    enemy_animations[i].Add(0, enemy_run_textures[i % enemy_types]);
  }

  Box enemy_boxes[enemies_count];
  VertexArray enemy_vertex_arrays[enemies_count];
  for (int i = 0; i < _countof(enemy_boxes); ++i) {
    // Box
    float width = enemy_run_textures[i % enemy_types][0].m_width;
    float height = enemy_run_textures[i % enemy_types][0].m_height;
    {
      VertexBuffer vertex_buffer;
      vertex_buffer.Initialize(width, height);

      enemy_vertex_arrays[i].Initialize();
      enemy_vertex_arrays[i].AddBuffer(&vertex_buffer, &vertex_buffer_layout);

      enemy_boxes[i].Initialize(&index_buffer, &enemy_vertex_arrays[i]);
    }

    // Position
    int x = 1 + rand() % arena_width;
    int y = arena_height * 0.8f + rand() % arena_height * 0.9f;

    Position position;
    position.Initialize({x, y});

    // Movement
    Movement movement;
    movement.Initialize({10, 0}, {10, 0}, 1.0f, 0);

    // Body
    Body body;
    body.Initialize(BodyType::NORMAL, {width, height});

    // Entities
    entity_manager.AddBox(i + 2, enemy_boxes[i]);
    entity_manager.AddAnimation(i + 2, enemy_animations[i]);
    entity_manager.AddProgram(i + 2, program);
    entity_manager.AddPosition(i + 2, position);
    entity_manager.AddMovement(i + 2, movement);
    entity_manager.AddBody(i + 2, body);
    entity_manager.AddToRenderer(i + 2, ImageType::ANIMATION);
    entity_manager.AddToPhysics(i + 2);
    entity_manager.AddToCollision(1, i + 2);
  }

  // Arena
  Position arena_position;
  arena_position.Initialize({0, 0});

  Body arena_body;
  arena_body.Initialize(BodyType::BOUNDING, {arena_width, arena_height});

  entity_manager.AddPosition(2 + enemies_count, arena_position);
  entity_manager.AddBody(2 + enemies_count, arena_body);

  for (int i = 2; i < 2 + enemies_count; ++i) {
    entity_manager.AddToCollision(2 + enemies_count, i);
  }

  // Player constraint
  Position player_constraint_position;
  player_constraint_position.Initialize({0, 0});

  Body player_constraint_body;
  player_constraint_body.Initialize(BodyType::BOUNDING, {glfw_manager.m_width, glfw_manager.m_height});

  entity_manager.AddPosition(2 + enemies_count + 1, player_constraint_position);
  entity_manager.AddBody(2 + enemies_count + 1, player_constraint_body);
  entity_manager.AddToCollision(2 + enemies_count + 1, 1);

  // NOTE(Vlad): User defined code

  // Callbacks
  collision_system.SetOnNormalCollision([&](int a, int b) {
    Health &health = entity_manager.m_healths.Get(a);
    --health.m_value;
  });

  collision_system.SetOnBoundingCollision([&](int b) {
    Position &position = entity_manager.m_positions.Get(b);
    if (b != 1) { // TODO: Add complete list of objects
      position.m_position.x = 1 + rand() % arena_width;
      position.m_position.y = arena_height * 0.8f + rand() % arena_height * 0.9f;
    } else { // Player
      if (position.m_position.x < 0) // NOTE(Vlad): If we collided on left side.
        position.m_position.x = glfw_manager.m_width * 0.95f;
      else
        position.m_position.x = 0;
    }
  });

  control_system.SetOnInputPlayer([&](int id, float dt) {
    // TODO: Movement based on box2d-lite later
    Movement &movement = entity_manager.m_movements[id];
    State &state = entity_manager.m_states.Get(id);
    Animation &animation = entity_manager.m_animations.Get(id);

    if (glfw_manager.IsKeyPressed(GLFW_KEY_A)) { // TODO: Replace with InputManager later for Android and other
      movement.m_velocity.x -= 200.0f;
      state.m_value = (int)PlayerState::RUN;
      animation.SetAnimation((int)PlayerState::RUN);
      player_vertex_buffer.BindData(&player_vertices_flipped, sizeof(player_vertices_flipped));
    } else if (glfw_manager.IsKeyPressed(GLFW_KEY_D)) {
      movement.m_velocity.x += 200.0f;
      state.m_value = (int)PlayerState::RUN;
      animation.SetAnimation((int)PlayerState::RUN);
      player_vertex_buffer.BindData(&player_vertices, sizeof(player_vertices));
    } else {
      state.m_value = (int)PlayerState::IDLE;
      animation.SetAnimation((int)PlayerState::IDLE);
    }
  });

  control_system.SetOnInputGlobal([&](float dt) {
    if (glfw_manager.IsKeyPressed(GLFW_KEY_ESCAPE)) {
      Global_GameState = GameState::MENU;
    }
  });

  interface_system.SetRender([&](int id) {
    imgui_manager.RenderBegin();

    ImGuiIO &io = ImGui::GetIO();

    ImGui::SetNextWindowPos(ImVec2(0, 0), 0, ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::SetNextWindowBgAlpha(0);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::Begin("Interface", NULL,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoBringToFrontOnFocus |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoScrollbar);

    switch (Global_GameState) {
      case GameState::MENU: {
        ImVec2 button_size = {100, 100};
        ImGui::SetCursorPos({glfw_manager.m_width / 2.0f - button_size.x * 0.5f, glfw_manager.m_height / 2.0f - button_size.y * 3});
        if (ImGui::Button("Play", button_size)) {
          Global_GameState = GameState::RUN;
        }
        ImGui::SetCursorPosX(glfw_manager.m_width / 2.0f - button_size.x * 0.5f);
        ImGui::Button("About", button_size);
        ImGui::SetCursorPosX(glfw_manager.m_width / 2.0f - button_size.x * 0.5f);
        if (ImGui::Button("Exit", button_size)) {
          Global_GameState = GameState::EXIT;
        }
      }
      break;
      case GameState::RUN: {
        Health health = entity_manager.m_healths.Get(id);
        
        ImGui::Text("Health: %d", health.m_value);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); 
      }
      break;
    }
    ImGui::PopStyleVar(2);
    ImGui::End();

    imgui_manager.RenderEnd();
  });

  Time time;
  time.Initialize();

  Win32Manager win32_manager;
  win32_manager.Initialize(&glfw_manager, &time, &entity_manager);
  win32_manager.Run();

  ExitProcess(0);
}

#endif