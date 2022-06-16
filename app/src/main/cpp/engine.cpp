// TODO: Make it easier to create animations lol

void Engine::Initialize(PlatformManager *platform_manager, AssetManager *asset_manager) {
  m_platform_manager = platform_manager;
  m_asset_manager = asset_manager;
}

void Engine::Script() {
  // Animations test

  // Animations
  for (int i = 0; i < sizeof(Global_AnimationInfo) / sizeof(AnimationInfo); ++i) {
    char *fmt = Global_AnimationInfo[i].m_fmt;
    int size = Global_AnimationInfo[i].m_size;

    Texture *textures = m_asset_manager->GetTextures(fmt, size);
    m_entity_manager.AddComponent<Array<Texture>>(i, Array<Texture> {textures});
  }

  // Shaders
  Shader vertex_shader;
  {
    const char *vertex_shader_code = R"(#version 300 es
                                     layout(location = 0) in vec4 position;
                                     layout(location = 1) in vec2 uv;

                                     out vec2 v_UV;

                                     uniform mat4 u_MVP;

                                     void main() {
                                     gl_Position = u_MVP * position;
                                     v_UV = uv;
                                     })";
    vertex_shader.Initialize(vertex_shader_code, GL_VERTEX_SHADER);
  }

  Shader fragment_shader;
  {
    const char *fragment_shader_code = R"(#version 300 es
        precision mediump float;
        layout(location = 0) out vec4 color;

        in vec2 v_UV;

        uniform sampler2D u_Texture;

        void main() {
        vec4 texture_vec4 = texture(u_Texture, v_UV);
        color = texture_vec4;
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

  // Systems
  AnimationSystem *animation_system = GetSystem<AnimationSystem>();
  ControlSystem *control_system = GetSystem<ControlSystem>();
  MovementSystem *movement_system = GetSystem<MovementSystem>();
  PhysicsSystem *physics_system = GetSystem<PhysicsSystem>();
  CollisionSystem *collision_system = GetSystem<CollisionSystem>();
  PlayerResetSystem *player_reset_system = GetSystem<PlayerResetSystem>();
  EnemyResetSystem *enemy_reset_system = GetSystem<EnemyResetSystem>();
  EffectSystem *effect_system = GetSystem<EffectSystem>();

  // Renderers
  BoxRenderer *box_renderer = GetRenderer<BoxRenderer>();
  InterfaceRenderer *interface_renderer = GetRenderer<InterfaceRenderer>();

  // Background
  Box background_box;
  background_box.Initialize(m_platform_manager->m_size);

  Position background_position {{0, 0}};

  Texture background_texture = m_asset_manager->GetTexture("background.png");

  RenderInfo background_render_info = {TextureType_Single, 1};

  Entity entity = m_entity_manager.CreateEntity();
  m_entity_manager.AddComponent<Box>(entity, background_box);
  m_entity_manager.AddComponent<Program>(entity, program);
  m_entity_manager.AddComponent<Position>(entity, background_position);
  m_entity_manager.AddComponent<Texture>(entity, background_texture);
  m_entity_manager.AddComponent<RenderInfo>(entity, background_render_info);

  box_renderer->AddEntity(entity);

  // Player
  const glm::vec2 player_size = {100, 100};

  Box player_box;
  player_box.Initialize(player_size);

  float player_vertices[] = {0, 0, 0.0f, 0.0f,
                         0, player_size.y,  0.0f, 1.0f,
                         player_size.x,  player_size.y,  1.0f, 1.0f,
                         player_size.x,  0, 1.0f, 0.0f};

  float player_vertices_flipped[] = {0, 0, 1.0f, 0.0f,
                     0, player_size.y,  1.0f, 1.0f,
                     player_size.x,  player_size.y,  0.0f, 1.0f,
                     player_size.x,  0, 0.0f, 0.0f};

  Position player_position;
  player_position.Initialize({m_platform_manager->m_size.x * 0.5f, 80});

  Movement player_movement;
  player_movement.Initialize({10, 0}, {10, 0}, 1, 0);

  Body player_body {BodyType_Box, player_size};

  Health player_health {3};

  Score player_score;

  Effect player_effect;
  player_effect.Initialize(1, 12.0f);

  Animation player_animation {AnimationType_PlayerIdle};

  RenderInfo player_render_info {TextureType_Animation, 1};

  entity = m_entity_manager.CreateEntity();
  m_entity_manager.AddComponent<Box>(entity, player_box);
  m_entity_manager.AddComponent<Animation>(entity, player_animation);
  m_entity_manager.AddComponent<Program>(entity, program);
  m_entity_manager.AddComponent<Position>(entity, player_position);
  m_entity_manager.AddComponent<Movement>(entity, player_movement);
  m_entity_manager.AddComponent<Body>(entity, player_body);
  m_entity_manager.AddComponent<Health>(entity, player_health);
  m_entity_manager.AddComponent<Score>(entity, player_score);
  m_entity_manager.AddComponent<RenderInfo>(entity, player_render_info);
  m_entity_manager.AddComponent<Effect>(entity, player_effect);
  
  control_system->AddEntity(entity);
  animation_system->AddEntity(entity);
  movement_system->AddEntity(entity);
  player_reset_system->AddEntity(entity);
  collision_system->AddEntity(entity, CollisionGroup_Player);
  effect_system->AddEntity(entity, EffectType_Blink);
  interface_renderer->AddEntity(entity);
  box_renderer->AddEntity(entity);

  // Arena
  const glm::vec2 arena_size = {m_platform_manager->m_size.x, m_platform_manager->m_size.y * 1.5f};

  Position arena_position;
  arena_position.Initialize({0, 0});

  Body arena_body;
  arena_body.Initialize(BodyType_BoundingBox, arena_size);

  entity = m_entity_manager.CreateEntity();
  m_entity_manager.AddComponent<Position>(entity, arena_position);
  m_entity_manager.AddComponent<Body>(entity, arena_body);

  collision_system->AddEntity(entity, CollisionGroup_Arena);

  // Bear, Bandit, Golem
  const int enemies_count = 10;
  const int enemy_types = 4;
  const glm::vec2 enemy_size = {50, 50};

  for (int i = 0; i < enemies_count; ++i) {
    int animation_type = Global_AnimationInfo[2 + i % (sizeof(Global_AnimationInfo) / sizeof(AnimationInfo) - 2)].m_type; // NOTE(Vlad): Done to avoid user animation
    Animation animation {animation_type};

    Box box;
    box.Initialize(enemy_size);

    Position position;
    position.Initialize(Game::GetEnemyPosition(arena_size));

    Movement movement;
    movement.Initialize({10, 0}, {10, 0}, 1, 0.005f);

    Body body {BodyType_Box, enemy_size};

    RenderInfo render_info {TextureType_Animation, 1};

    entity = m_entity_manager.CreateEntity();
    m_entity_manager.AddComponent<Box>(entity, box);
    m_entity_manager.AddComponent<Animation>(entity, animation);
    m_entity_manager.AddComponent<Program>(entity, program);
    m_entity_manager.AddComponent<Position>(entity, position);
    m_entity_manager.AddComponent<Movement>(entity, movement);
    m_entity_manager.AddComponent<Body>(entity, body);
    m_entity_manager.AddComponent<RenderInfo>(entity, render_info);

    animation_system->AddEntity(entity);
    movement_system->AddEntity(entity);
    physics_system->AddEntity(entity);
    enemy_reset_system->AddEntity(entity);
    collision_system->AddEntity(entity, CollisionGroup_Enemy);
    box_renderer->AddEntity(entity);

    // TODO: Score area
  }

  // Initial state
  Global_GameState = GameState_Menu;
}

void Engine::Loop() {
  int old_time = GetMilliseconds();
  int extra_time = 0;
  int frame_time = 1000 / MAX_FPS;
  while (!m_platform_manager->ShouldClose() && Global_GameState != GameState_Exit) {
    int new_time = GetMilliseconds();
    int time = new_time - old_time;

    /////// FRAME ///////

    if (m_platform_manager->IsFocused()) {
      extra_time += time;

      while (extra_time >= frame_time) {
        m_platform_manager->PollEvents();

        Update(frame_time / 1000.0f);

        extra_time -= frame_time;
      }
      
      Render();
    } else {
      Utility::Wait(1);

      m_platform_manager->PollEvents();
    }

    m_platform_manager->SwapBuffers();

    /////// END FRAME ///////

    old_time = new_time;
  }
}

void Engine::Render() {
  glCall(glClearColor(0.0, 0.0, 0.0, 1.0f));
  glCall(glClear(GL_COLOR_BUFFER_BIT));

  glCall(glEnable(GL_BLEND));
  glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  // NOTE(Vlad): Do you need that?
  glViewport(0, 0, m_platform_manager->m_size.x, m_platform_manager->m_size.y);

  for (int i = 0; i < hmlen(m_renderers); ++i) {
    m_renderers[i].value->Render(&m_entity_manager);
  }
}

void Engine::Update(float dt) {
  if (Global_GameState != GameState_Menu) {
    for (int i = 0; i < hmlen(m_systems); ++i) {
      m_systems[i].value->Update(&m_entity_manager, dt);
    }
  }
}

template <typename T>
void Engine::AddSystem(ISystem *system) {
  std::type_index type_index = std::type_index(typeid(T));
  hmput(m_systems, type_index, system);
}

template <typename T>
T *Engine::GetSystem() {
  std::type_index type_index = std::type_index(typeid(T));
  return (T *)hmget(m_systems, type_index);
}

template <typename T>
void Engine::AddRenderer(IRenderer *renderer) {
  std::type_index type_index = std::type_index(typeid(T));
  hmput(m_renderers, type_index, renderer);
}

template <typename T>
T *Engine::GetRenderer() {
  std::type_index type_index = std::type_index(typeid(T));
  return (T *)hmget(m_renderers, type_index);
}