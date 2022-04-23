// TODO: Add warnings when Texture and Animation bound at the same time (Static
// vs. Dynamic)

void EntityManager::Initialize(CameraSystem *camera_system,
                               RendererSystem *renderer_system,
                               PhysicsSystem *physics_system,
                               CollisionSystem *collision_system,
                               FollowSystem *follow_system,
                               ControlSystem *control_system, InterfaceSystem *interface_system) {
  m_animations = NULL;
  m_boxes = NULL;
  m_states = NULL;
  m_programs = NULL;
  m_textures = NULL;
  m_positions = NULL;
  m_movements = NULL;
  m_bodies = NULL;
  m_healths = NULL;
  m_physics_system = physics_system;
  m_physics_system_ids = NULL;
  m_renderer_system = renderer_system;
  m_renderer_system_ids = NULL;
  m_collision_system = collision_system;
  m_collision_pairs = NULL;
  m_camera_system = camera_system;
  m_camera_system_id = -1;
  m_follow_system = follow_system;
  m_follow_map = NULL;
  m_control_system = control_system;
  m_control_system_id = -1;
  m_interface_system = interface_system;
  m_interface_system_id = -1;

  // Test
  m_components = NULL;
}

void EntityManager::AddAnimation(int id, Animation *animation) {
  hmput(m_animations, id, animation);
}

void EntityManager::AddBox(int id, Box *box) { hmput(m_boxes, id, box); }

void EntityManager::AddProgram(int id, Program *program) {
  hmput(m_programs, id, program);
}

void EntityManager::AddTexture(int id, Texture *texture) {
  hmput(m_textures, id, texture);
}

void EntityManager::AddPosition(int id, Position *position) {
  hmput(m_positions, id, position);
}

void EntityManager::AddMovement(int id, Movement *movement) {
  hmput(m_movements, id, movement);
}

void EntityManager::AddBody(int id, Body *body) { hmput(m_bodies, id, body); }

void EntityManager::AddState(int id, State *state) {
  hmput(m_states, id, state);
}

void EntityManager::AddHealth(int id, Health *health) {
  hmput(m_healths, id, health);
}

void EntityManager::SetToCamera(int id) { m_camera_system_id = id; }

void EntityManager::SetToControl(int id) { m_control_system_id = id; }

void EntityManager::SetToInterface(int id) {
  m_interface_system_id = id;
}

void EntityManager::AddToPhysics(int id) { arrput(m_physics_system_ids, id); }

void EntityManager::AddToRenderer(int id) { arrput(m_renderer_system_ids, id); }

void EntityManager::AddToCollision(int a, int b) {
  CollisionPair pair = {a, b};
  arrput(m_collision_pairs, pair);
}

void EntityManager::AddToFollow(int a, int b) { hmput(m_follow_map, a, b); }

void EntityManager::RemoveFromCollision(int id) { arrdel(m_collision_pairs, id); }

void EntityManager::RemoveFromPhysics(int id) {
  for (int i = 0; i < arrlen(m_physics_system_ids); ++i) {
    if (m_physics_system_ids[i] == id) {
      arrdel(m_physics_system_ids, i);
      break;
    }
  }
}

void EntityManager::RemoveFromRender(int id) {
  for (int i = 0; i < arrlen(m_renderer_system_ids); ++i) {
    if (m_renderer_system_ids[i] == id) {
      arrdel(m_renderer_system_ids, i);
      break;
    }
  }
}

void EntityManager::Old(float dt) {
  if (Global_GameState != GameState::RUN) {
    return;
  }
  
  for (int i = 0; i < hmlen(m_bodies); ++i) {
    Position *position = hmget(m_positions, m_bodies[i].key);

    m_bodies[i].value->Update(position, dt);
  }

  for (int i = 0; i < hmlen(m_movements); ++i) {
    Position *position = hmget(m_positions, m_movements[i].key);

    m_movements[i].value->Update(position, dt); // TODO: Add Physics component instead of this, and make MovementSystem
  }

  for (int i = 0; i < hmlen(m_animations); ++i) {
    State *state = hmget(m_states, m_animations[i].key);

    if (!state) {
      m_animations[i].value->Update(dt);
    } else {
      m_animations[i].value->Update(state, dt);
    }
  }

  // Systems
  if (m_control_system_id != -1) {
    Movement *movement = hmget(m_movements, m_control_system_id);
    State *state = hmget(m_states, m_control_system_id);

    if (m_control_system->m_on_input_player) {
      m_control_system->m_on_input_player(m_control_system_id, dt);
    }
  }

  if (m_control_system->m_on_input_global) {
    m_control_system->m_on_input_global(dt);
  }

  for (int i = 0; i < arrlen(m_physics_system_ids); ++i) {
    Movement *movement = hmget(m_movements, m_physics_system_ids[i]);

    m_physics_system->Update(movement, dt);
  }

  for (int i = 0; i < arrlen(m_collision_pairs); ++i) {
    int ida = m_collision_pairs[i].a;
    int idb = m_collision_pairs[i].b;
    Body *ba = hmget(m_bodies, ida);
    Body *bb = hmget(m_bodies, idb);
    Movement *ma = hmget(m_movements, ida);
    Movement *mb = hmget(m_movements, idb);

    m_collision_system->Update(ida, idb, ba, bb, ma,
                               mb, dt);
  }

  for (int i = 0; i < hmlen(m_follow_map); ++i) {
    Position *a = hmget(m_positions, m_follow_map[i].key);
    Position *b = hmget(m_positions, m_follow_map[i].value);

    m_follow_system->Update(a, b);
  }

  if (m_camera_system_id != -1) {
    Position *a = m_camera_system->m_position;
    Position *b = hmget(m_positions, m_camera_system_id);

    m_follow_system->Update(a, b);
  }
}

void EntityManager::New(float dt) {
  for (int i = 0; i < hmlen(m_components); ++i) { // Component types
    int type = m_components[i].key;

    ComponentMap *component_map = m_components[type].value;
    for (int j = 0; j < hmlen(component_map); ++j) { // Entities
      int id = component_map[j].key;
      switch (type) {
      case Components::ANIMATION: {
        State *state = (State *)GetComponent((int)Components::STATE, id);
        Animation *animation = (Animation *)component_map[id].value;

        animation->Update(state, dt);
      } break;
      }
    }
  }
  // Animation *animation = (Animation
  // *)GetComponent((int)::Components::ANIMATION, 1);

  // for (int i = 0; i < hmlen(m_bodies); ++i) {
  //   Position *position = hmget(m_positions, m_bodies[i].key);

  //   m_bodies[i].value->Update(position, dt);
  // }

  // for (int i = 0; i < hmlen(m_movements); ++i) {
  //   Position *position = hmget(m_positions, m_movements[i].key);

  //   m_movements[i].value->Update(position, dt);
  // }

  // for (int i = 0; i < hmlen(m_animations); ++i) {
  //   State *state = hmget(m_states, m_animations[i].key);

  //   if (!state) {
  //     m_animations[i].value->Update(dt);
  //   } else {
  //     m_animations[i].value->Update(state, dt);
  //   }
  // }
}

void EntityManager::Update(float dt) {
  ////// Test //////

  // Components
  static double accumulator = 0.0;
  static int count = 0;
  StartCounter();
  Old(dt);
  double time = GetCounter();
  accumulator += time;
  count++;

  if (count == 500) { // NOTE(Vlad): Need a looooot more components to test, for
                      // now test is garbage
    std::cout << accumulator / count << std::endl;
    accumulator = 0;
    count = 0;
  }
}

void EntityManager::Render() {
  for (int i = 0; i < arrlen(m_renderer_system_ids); ++i) {
    int id = m_renderer_system_ids[i];

    Box *box = hmget(m_boxes, id);
    Position *position = hmget(m_positions, id);
    Animation *animation = hmget(m_animations, id);
    Program *program = hmget(m_programs, id);
    Texture *texture = hmget(m_textures, id);

    // Box *box = (Box *)GetComponent(id, (int)Components::BOX);
    // Position *position = (Position *)GetComponent(id,
    // (int)Components::POSITION); Animation *animation = (Animation
    // *)GetComponent(id, (int)Components::ANIMATION); Program *program =
    // (Program *)GetComponent(id, (int)Components::PROGRAM); Texture *texture =
    // (Texture *)GetComponent(id, (int)Components::TEXTURE);

    m_renderer_system->RenderBoxBegin(position, m_camera_system, program);

    if (animation) { // TODO: Use bit flags for this
      program->SetUniform1i("u_Texture", 0);

      texture = animation->GetCurrentTexture();
      texture->Bind();
    } else if (texture) {
      program->SetUniform1i("u_Texture", 0);
      texture->Bind();
    }

    box->Bind();
    box->Draw();
    box->Unbind();

    if (animation || texture) { // TODO: Use bit flags for this
      texture->Unbind();
    }

    m_renderer_system->RenderBoxEnd(program);
  }

  if (m_interface_system->m_render && m_interface_system_id != -1) {
    m_interface_system->m_render(m_interface_system_id); // User code
  }
}