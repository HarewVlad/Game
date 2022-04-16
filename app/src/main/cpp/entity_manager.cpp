// TODO: Add warnings when Texture and Animation bound at the same time (Static
// vs. Dynamic)

void EntityManager::Initialize(CameraSystem *camera_system, RendererSystem *renderer_system,
                               PhysicsSystem *physics_system, CollisionSystem *collision_system, FollowSystem *follow_system, ControlSystem *control_system) {
  m_animations = NULL;
  m_boxes = NULL;
  m_states = NULL;
  m_programs = NULL;
  m_textures = NULL;
  m_positions = NULL;
  m_movements = NULL;
  m_bodies = NULL;
  m_physics_system = physics_system;
  m_physics_system_ids = NULL;
  m_renderer_system = renderer_system;
  m_renderer_system_ids = NULL;
  m_collision_system = collision_system;
  m_collision_map = NULL;
  m_camera_system = camera_system;
  m_camera_system_id = -1;
  m_follow_system = follow_system;
  m_follow_map = NULL;
  m_control_system = control_system;
  m_control_system_id = -1;

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

void EntityManager::AddBody(int id, Body *body) {
  hmput(m_bodies, id, body);
}

void EntityManager::AddState(int id, State *state) {
  hmput(m_states, id, state);
}

void EntityManager::RemoveAnimation(int id) {
  hmdel(m_animations, id);
}

void EntityManager::RemoveBox(int id) {
  hmdel(m_boxes, id);
}

void EntityManager::RemoveProgram(int id) {
  hmdel(m_programs, id);
}

void EntityManager::RemoveTexture(int id) {
  hmdel(m_textures, id);
}

void EntityManager::RemovePosition(int id) {
  hmdel(m_positions, id);
}

void EntityManager::RemoveMovement(int id) {
  hmdel(m_movements, id);
}

void EntityManager::RemoveBody(int id) {
  hmdel(m_bodies, id);
}

void EntityManager::SetToCamera(int id) {
  m_camera_system_id = id;
}

void EntityManager::SetToControl(int id) {
  m_control_system_id = id;
}

void EntityManager::AddToPhysics(int id) { arrput(m_physics_system_ids, id); }

void EntityManager::AddToRenderer(int id) { arrput(m_renderer_system_ids, id); }

void EntityManager::AddToCollision(int a, int b) { hmput(m_collision_map, a, b); }

void EntityManager::AddToFollow(int a, int b) {
  hmput(m_follow_map, a, b);
}

void EntityManager::RemoveFromCollision(int id) {
  hmdel(m_collision_map, id);
}

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
  // for (int i = 0; i < hmlen(m_controls); ++i) {
  //   Movement *movement = hmget(m_movements, m_controls[i].key);
  //   Animation *animation = hmget(m_animations, m_controls[i].key);

  //   m_controls[i].value->Update(movement, animation, dt); // TODO: Rethink where need to change animation ids
  //   // Solution:
  //   // 1. Create State component
  //   // 2. Pass it to Control and Animation
  //   // 3. Control changes state, Animation adapts to changes
  //   // EX: void Update(Movement *movement, State *state); for control
  //   // void Update(State *state) for animation;
  //   // 4. Bind animations to State
  //   // 5. EZ
  // }

  for (int i = 0; i < hmlen(m_bodies); ++i) {
    Position *position = hmget(m_positions, m_bodies[i].key);

    m_bodies[i].value->Update(position, dt);
  }

  for (int i = 0; i < hmlen(m_movements); ++i) {
    Position *position = hmget(m_positions, m_movements[i].key);

    m_movements[i].value->Update(position, dt);
  }

  for (int i = 0; i < hmlen(m_animations); ++i) {
    State *state = hmget(m_states, m_animations[i].key);

    if (!state) {
      m_animations[i].value->Update(dt);
    } else {
      m_animations[i].value->Update(state, dt);
    }
  }
}

void EntityManager::New(float dt) {
  for (int i = 0; i < hmlen(m_components); ++i) {
    void **array = hmget(m_components, m_components[i].key);

    for (int j = 0; j < arrlen(array); ++j) {
      void *component = array[j];

      if (component)
      switch (j) {
        case Components::ANIMATION: {
          ((Animation *)component)->Update(dt);
        }
        break;
        case Components::PROGRAM:
        break;
        case Components::TEXTURE:
        break;
        case Components::POSITION:
        break;
        case Components::MOVEMENT: {
          Position *position = (Position *)array[(int)Components::POSITION];

          ((Movement *)component)->Update(position, dt);
        }
        break;
        case Components::BODY: {
          Position *position = (Position *)array[(int)Components::POSITION];

          ((Body *)component)->Update(position, dt);
        }
        break;
      }
    }
  }
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

  if (count == 500) {
    std::cout << accumulator / count << std::endl;
    accumulator = 0;
    count = 0;
  }

  // Systems

  if (m_control_system_id != -1) {
    Movement *movement = hmget(m_movements, m_control_system_id);
    State *state = hmget(m_states, m_control_system_id);

    if (m_control_system->m_update) {
      m_control_system->m_update(movement, state, dt);
    }
  }

  for (int i = 0; i < arrlen(m_physics_system_ids); ++i) {
    Movement *movement = hmget(m_movements, m_physics_system_ids[i]);

    m_physics_system->Update(movement, dt);
  }

  for (int i = 0; i < hmlen(m_collision_map); ++i) {
    int id_a = m_collision_map[i].key;
    int id_b = m_collision_map[i].value;
    Body *body_a = hmget(m_bodies, id_a);
    Body *body_b = hmget(m_bodies, id_b);
    Movement *movement_a = hmget(m_movements, id_a);
    Movement *movement_b = hmget(m_movements, id_b);

    m_collision_system->Update(id_a, id_b, body_a, body_b, movement_a, movement_b, dt);
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

void EntityManager::Render() {
  for (int i = 0; i < arrlen(m_renderer_system_ids); ++i) {
    int id = m_renderer_system_ids[i];

    Box *box = hmget(m_boxes, id);
    Position *position = hmget(m_positions, id);
    Animation *animation = hmget(m_animations, id);
    Program *program = hmget(m_programs, id);
    Texture *texture = hmget(m_textures, id);

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
}