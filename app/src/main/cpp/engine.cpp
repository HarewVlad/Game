// TODO: Make it easier to create animations lol

void Engine::Initialize(WindowManager *window_manager, ImGuiManager *imgui_manager, PathManager *path_manager, InputManager *input_manager) {
  m_window_manager = window_manager;
  m_input_manager = input_manager;
  m_imgui_manager = imgui_manager;
  m_path_manager = path_manager;

  // Systems
  // TODO: Think about systems and how can we add custom systems (Steel code from Unity DOTS i guess=))
  m_camera_system.Initialize({0, 0});
  m_renderer_system.Initialize(window_manager);
  m_physics_system.Initialize(GRAVITY);
  m_collision_system.Initialize();
  m_follow_system.Initialize(window_manager);
  m_interface_system.Initialize(imgui_manager);

  // Entity manager
  m_entity_manager.Initialize(&m_camera_system, &m_renderer_system, &m_physics_system, &m_collision_system, &m_follow_system, &m_control_system, &m_interface_system);
}

void Engine::Start() {
  IndexBuffer index_buffer;
  index_buffer.Initialize();

  VertexBufferLayout vertex_buffer_layout;
  vertex_buffer_layout.Initialize();

  // Background
  Texture background_texture;
  m_path_manager->GetTexture(&background_texture, "background.png");
  m_entity_manager.AddTexture(background_texture);

  // Player
  Texture player_idle_textures[4];
  Texture player_run_textures[8];
  m_path_manager->GetTextures(player_idle_textures, 4, "player/idle/%d.png");
  m_path_manager->GetTextures(player_run_textures, 8, "player/run/%d.png");

  // Enemy
  Texture enemy_bear_textures[4];
  Texture enemy_bandit_textures[4];
  Texture enemy_golem_textures[6];
  Texture enemy_ent_textures[4];
  m_path_manager->GetTextures(enemy_bear_textures, 4, "bear/%d.png");
  m_path_manager->GetTextures(enemy_bandit_textures, 4, "bandit/%d.png");
  m_path_manager->GetTextures(enemy_golem_textures, 6, "golem/%d.png");
  m_path_manager->GetTextures(enemy_ent_textures, 4, "ent/%d.png");

  // Get animation ranges
  Range player_idle_range = m_entity_manager.AddTextures(player_idle_textures, 4);
  Range player_run_range = m_entity_manager.AddTextures(player_run_textures, 8);

  Range enemy_animation_ranges[4];
  enemy_animation_ranges[0] = m_entity_manager.AddTextures(enemy_bear_textures, 4);
  enemy_animation_ranges[1] = m_entity_manager.AddTextures(enemy_bandit_textures, 4);
  enemy_animation_ranges[2] = m_entity_manager.AddTextures(enemy_golem_textures, 6);
  enemy_animation_ranges[3] = m_entity_manager.AddTextures(enemy_ent_textures, 4);

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

  // Background
  Box background_box;
  VertexArray background_vertex_array;
  float background_width = m_window_manager->m_size.x;
  float background_height = m_window_manager->m_size.y;
  {
    VertexBuffer vertex_buffer;
    vertex_buffer.Initialize(background_width, background_height); // TODO: Why not just pass glm::vec2?

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

  m_entity_manager.SetEntity(0);
  m_entity_manager.AddBox(background_box);
  m_entity_manager.AddProgram(program);
  m_entity_manager.AddPosition(background_position);
  m_entity_manager.AddToRenderer(ImageType::TEXTURE);

  // Player

  // Custom player components
  enum class PlayerState {
    IDLE,
    RUN
  };

  State player_state;
  player_state.Initialize((int)PlayerState::IDLE);

  Health player_health;
  player_health.Initialize(3);

  Score player_score;
  player_score.Initialize();
  //

  Animation player_animation;
  player_animation.Initialize();
  player_animation.Add((int)PlayerState::IDLE, player_idle_range);
  player_animation.Add((int)PlayerState::RUN, player_run_range);

  Box player_box;
  VertexBuffer player_vertex_buffer;
  VertexArray player_vertex_array;
  float player_width = 100;
  float player_height = 100;

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
  player_position.Initialize({m_window_manager->m_size.x * 0.5f, 80});

  Movement player_movement;
  player_movement.Initialize({10, 0}, {10, 0}, 1.0f, 0);

  Body player_body;
  player_body.Initialize(BodyType::NORMAL, {player_width, player_height});

  EffectBlink player_effect_blink;
  player_effect_blink.Initialize(1, 12.0f);

  m_entity_manager.SetEntity(1);
  m_entity_manager.AddBox(player_box);
  m_entity_manager.AddAnimation(player_animation);
  m_entity_manager.AddProgram(program);
  m_entity_manager.AddPosition(player_position);
  m_entity_manager.AddMovement(player_movement);
  m_entity_manager.AddBody(player_body);
  m_entity_manager.AddToRenderer(ImageType::ANIMATION);
  m_entity_manager.AddBlink(1, player_effect_blink);
  m_entity_manager.SetToControl();
  m_entity_manager.SetToInterface();

  // Arena size
  int arena_width = m_window_manager->m_size.x;
  int arena_height = m_window_manager->m_size.y * 1.5f;

  // Bear, Bandit, Golem
  auto GetEnemyPositionX = [](int width) {
    return 1 + rand() % width;
  };

  auto GetEnemyPositionY = [](int height) {
    return height * 0.8f + rand() % height * 0.9f;
  };

  const int enemies_count = 10;
  const int enemy_types = 4;

  Animation enemy_animations[enemies_count];
  for (int i = 0; i < sizeof(enemy_animations) / sizeof(Animation); ++i) {
    enemy_animations[i].Initialize();
    enemy_animations[i].Add(0, enemy_animation_ranges[i % enemy_types]);
  }

  Box enemy_boxes[enemies_count];
  VertexArray enemy_vertex_arrays[enemies_count];
  for (int i = 0; i < enemies_count; ++i) {
    // Box
    float width = 50;
    float height = 50;
    {
      VertexBuffer vertex_buffer;
      vertex_buffer.Initialize(width, height);

      enemy_vertex_arrays[i].Initialize();
      enemy_vertex_arrays[i].AddBuffer(&vertex_buffer, &vertex_buffer_layout);

      enemy_boxes[i].Initialize(&index_buffer, &enemy_vertex_arrays[i]);
    }

    // Position
    int x = GetEnemyPositionX(arena_width);
    int y = GetEnemyPositionY(arena_height);

    Position position;
    position.Initialize({x, y});

    // Movement
    Movement movement;
    movement.Initialize({10, 0}, {10, 0}, 1.0f, 0);

    // Body
    Body body;
    body.Initialize(BodyType::NORMAL, {width, height});

    // Entities
    m_entity_manager.SetEntity(i + 2);
    m_entity_manager.AddBox(enemy_boxes[i]);
    m_entity_manager.AddAnimation(enemy_animations[i]);
    m_entity_manager.AddProgram(program);
    m_entity_manager.AddPosition(position);
    m_entity_manager.AddMovement(movement);
    m_entity_manager.AddBody(body);
    m_entity_manager.AddToRenderer(ImageType::ANIMATION);
    m_entity_manager.AddToPhysics();
    m_entity_manager.AddToCollision(1, i + 2);

    // Score area // TODO: FIX BUG
    Body score_body;
    score_body.Initialize(BodyType::NORMAL, {width * 3, height * 3});

    // m_entity_manager.AddPositionReference(i + 2 + enemies_count, i + 2);
    // m_entity_manager.AddPosition(i + 123123, position);
    // m_entity_manager.AddBody(i + 123123, score_body);
    // m_entity_manager.AddToCollision(1, i + 123123);
  }

  // Arena
  Position arena_position;
  arena_position.Initialize({0, 0});

  Body arena_body;
  arena_body.Initialize(BodyType::BOUNDING, {arena_width, arena_height});

  m_entity_manager.AddPosition(2 + enemies_count, arena_position);
  m_entity_manager.AddBody(2 + enemies_count, arena_body);

  for (int i = 2; i < 2 + enemies_count; ++i) {
    m_entity_manager.AddToCollision(2 + enemies_count, i);
  }

  // Player constraint
  Position player_constraint_position;
  player_constraint_position.Initialize({0, 0});

  Body player_constraint_body;
  player_constraint_body.Initialize(BodyType::BOUNDING, {m_window_manager->m_size.x, m_window_manager->m_size.y});

  m_entity_manager.AddPosition(2 + enemies_count * 2 + 1, player_constraint_position);
  m_entity_manager.AddBody(2 + enemies_count * 2 + 1, player_constraint_body);
  m_entity_manager.AddToCollision(2 + enemies_count * 2 + 1, 1);

  auto GameReset = [&]() {
    // Player
    player_health.Initialize(3);
    player_score.Initialize();

    // Enemies
    // TODO: Adequate method of storing and accessing entities through entity id
    for (int i = 0; i < enemies_count; ++i) {
      Position &position = m_entity_manager.m_positions.Value(i + 2);
      position.m_xy.x = GetEnemyPositionX(arena_width);
      position.m_xy.y = GetEnemyPositionY(arena_height);

      Movement &movement = m_entity_manager.m_movements[i + 2];
      movement.m_velocity = {0, 0};
      movement.m_acceleration = {0, 0};
    }

    Global_GameState = GameState::RUN;
  };

  // Callbacks
  m_collision_system.SetOnNormalCollision([&](int a, int b) {
    EffectBlink &player_effect_blink = m_entity_manager.m_effect_blinks.Value(a);
    if (!player_effect_blink.IsExecuting()) {
      --player_health.m_value;
      ++player_score.m_value;

      player_effect_blink.Start();
    }

    if (!player_health.m_value) {
      GameReset();
    }
  });

  m_collision_system.SetOnBoundingCollision([&](int b) {
    Position &position = m_entity_manager.m_positions.Value(b);
    if (b != 1) { // TODO: Add complete list of objects
      position.m_xy.x = GetEnemyPositionX(arena_width);
      position.m_xy.y = GetEnemyPositionY(arena_height);
    } else { // Player
      if (position.m_xy.x < 0) // NOTE(Vlad): If we collided on left side.
        position.m_xy.x = m_window_manager->m_size.x * 0.95f;
      else
        position.m_xy.x = 0;
    }
  });

// m_control_system.SetOnInputPlayer([&](int id, float dt) {
//   Movement &movement = m_entity_manager.m_movements[id];
//   Animation &animation = m_entity_manager.m_animations.Value(id);
//
//   if (m_input_manager->IsKeyPressed(GLFW_KEY_A)) { // TODO: Replace with InputManager later for Android and other
//     movement.m_velocity.x -= 200.0f;
//     player_state.m_value = (int)PlayerState::RUN;
//     animation.SetAnimation((int)PlayerState::RUN);
//     player_vertex_buffer.BindData(&player_vertices_flipped, sizeof(player_vertices_flipped));
//   } else if (m_input_manager->IsKeyPressed(GLFW_KEY_D)) {
//     movement.m_velocity.x += 200.0f;
//     player_state.m_value = (int)PlayerState::RUN;
//     animation.SetAnimation((int)PlayerState::RUN);
//     player_vertex_buffer.BindData(&player_vertices, sizeof(player_vertices));
//   } else {
//     player_state.m_value = (int)PlayerState::IDLE;
//     animation.SetAnimation((int)PlayerState::IDLE);
//   }
// });

// m_control_system.SetOnInputGlobal([&](float dt) {
//   if (m_input_manager->IsKeyPressed(GLFW_KEY_ESCAPE)) {
//     Global_GameState = GameState::MENU;
//   }
// });

  m_interface_system.SetRender([&](int id) { // TODO: Make ISystem derived, so user can specify system and bind it to EntityManager?
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
        ImGui::SetCursorPos({io.DisplaySize.x / 2.0f - button_size.x * 0.5f, io.DisplaySize.y / 2.0f - button_size.y * 3});
        if (ImGui::Button("Play", button_size)) {
          Global_GameState = GameState::RUN;
        }
        ImGui::SetCursorPosX(io.DisplaySize.x / 2.0f - button_size.x * 0.5f);
        if (ImGui::Button("Reset", button_size)) {
          GameReset();
        }

        ImGui::SetCursorPosX(io.DisplaySize.x / 2.0f - button_size.x * 0.5f);
        ImGui::Button("About", button_size);
        ImGui::SetCursorPosX(io.DisplaySize.x / 2.0f - button_size.x * 0.5f);
        if (ImGui::Button("Exit", button_size)) {
          Global_GameState = GameState::EXIT;
        }
      }
      break;
      case GameState::RUN: {
        ImGui::Text("Health: %d", player_health.m_value);
        ImGui::SetCursorPosX(io.DisplaySize.x / 2);
        ImGui::Text("Score: %d", player_score.m_value);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); 
      }
      break;
      default:
      break;
    }
    ImGui::PopStyleVar(2);
    ImGui::End();
  });

  // Set initial state
  Global_GameState = GameState::MENU;

  // NOTE(Vlad): Call it here, because have some issues with storage of some structs, need to think about it later
  Loop();
}

void Engine::Loop() {
  int old_time = GetMilliseconds();
  int extra_time = 0;
  int frame_time = 1000 / MAX_FPS;
  while (!m_window_manager->WindowShouldClose() && Global_GameState != GameState::EXIT) {
    int new_time = GetMilliseconds();
    int time = new_time - old_time;

    ////// FRAME ///////

    if (m_window_manager->IsWindowFocused()) {
      extra_time += time;

      while (extra_time >= frame_time) {
        m_window_manager->PollEvents();

        Update(frame_time / 1000.0f);

        extra_time -= frame_time;
      }
      
      Render();
    } else {
      Utility::Wait(5);

      m_window_manager->PollEvents();
    }

    m_window_manager->SwapBuffers();

    /////// END FRAME ///////

    old_time = new_time;
  }
}

void Engine::Render() {
  glCall(glClearColor(0.0, 0.0, 0.0, 1.0f));
  glCall(glClear(GL_COLOR_BUFFER_BIT));

  glCall(glEnable(GL_BLEND));
  glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  // TODO: Do i need that?
  glViewport(0, 0, m_window_manager->m_size.x, m_window_manager->m_size.y);

  m_entity_manager.Render();
}

void Engine::Update(float dt) {
  m_entity_manager.Update(dt);
}