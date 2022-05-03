// TODO: Add warnings when Texture and Animation bound at the same time (Static
// vs. Dynamic)

void EntityManager::Initialize(CameraSystem *camera_system,
                               RendererSystem *renderer_system,
                               PhysicsSystem *physics_system,
                               CollisionSystem *collision_system,
                               FollowSystem *follow_system,
                               ControlSystem *control_system, InterfaceSystem *interface_system) {
  m_movements = NULL;
  m_physics_system = physics_system;
  m_physics_system_ids = NULL;
  m_renderer_system = renderer_system;
  m_renderer_system_data = NULL;
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
  m_textures = NULL;
}

void EntityManager::AddAnimation(int id, Animation animation) {
  m_animations.Add(id, animation);
}

void EntityManager::AddBox(int id, Box box) {
  m_boxes.Add(id, box);
}

void EntityManager::AddProgram(int id, Program program) {
  m_programs.Add(id, program);
}

void EntityManager::AddTexture(Texture texture) {
  arrput(m_textures, texture);
}

void EntityManager::AddPosition(int id, Position position) {
  m_positions.Add(id, position);
}

void EntityManager::AddPositionReference(int ida, int idb) {
  m_positions.AddReference(ida, idb);
}

void EntityManager::AddMovement(int id, Movement movement) {
  if (id >= arrlen(m_movements)) {
    arrsetlen(m_movements, id);
  }
  arrins(m_movements, id, movement);
}

void EntityManager::AddBody(int id, Body body) {
  m_bodies.Add(id, body);
}

void EntityManager::AddState(int id, State state) {
  m_states.Add(id, state);
}

void EntityManager::SetToCamera(int id) { m_camera_system_id = id; }

void EntityManager::SetToControl(int id) { m_control_system_id = id; }

void EntityManager::SetToInterface(int id) {
  m_interface_system_id = id;
}

void EntityManager::AddToPhysics(int id) { arrput(m_physics_system_ids, id); }

void EntityManager::AddToRenderer(int id, ImageType type) {
  RendererData data = {id, type};; 
  arrput(m_renderer_system_data, data);
}

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

void EntityManager::Old(float dt) {
  if (Global_GameState != GameState::RUN) {
    return;
  }

  for (int i = 0; i < arrlen(m_movements); ++i) {
    Position &position = m_positions.Get(i);

    m_movements[i].Update(&position, dt); // TODO: Add Physics component instead of this, and make MovementSystem
  }

  for (int i = 0; i < arrlen(m_animations.m_array); ++i) {
    m_animations.m_array[i].Update(dt);
  }

  // Systems
  if (m_control_system_id != -1) {
    if (m_control_system->m_on_input_player) {
      m_control_system->m_on_input_player(m_control_system_id, dt);
    }
  }

  if (m_control_system->m_on_input_global) {
    m_control_system->m_on_input_global(dt);
  }

  for (int i = 0; i < arrlen(m_physics_system_ids); ++i) {
    Movement &movement = m_movements[m_physics_system_ids[i]];

    m_physics_system->Update(&movement, dt);
  }

  for (int i = 0; i < arrlen(m_collision_pairs); ++i) {
    int ida = m_collision_pairs[i].a;
    int idb = m_collision_pairs[i].b;
    Body &ba = m_bodies.Get(ida);
    Body &bb = m_bodies.Get(idb);
    Position &pa = m_positions.Get(ida);
    Position &pb = m_positions.Get(idb);

    m_collision_system->Update(ida, idb, &ba, &bb, &pa,
                               &pb, dt);
  }

  for (int i = 0; i < hmlen(m_follow_map); ++i) {
    Position &a = m_positions.Get(m_follow_map[i].key);
    Position &b = m_positions.Get(m_follow_map[i].value);

    m_follow_system->Update(&a, &b);
  }

  if (m_camera_system_id != -1) {
    Position *a = m_camera_system->m_position;
    Position &b = m_positions.Get(m_camera_system_id);

    m_follow_system->Update(a, &b);
  }
}

void EntityManager::Update(float dt) {
  static double accumulator = 0.0;
  static int count = 0;
  StartCounter();
  Old(dt);
  double time = GetCounter();
  accumulator += time;
  count++;

  if (count == 500) {
    std::cout << "Update: " << accumulator / count << std::endl;
    accumulator = 0;
    count = 0;
  }
}

void EntityManager::Render() {
  static double accumulator = 0.0;
  static int count = 0;
  StartCounter();
  if (Global_GameState == GameState::RUN) { // TODO: Mb move render to user code, so the user can specify what he wants?
    for (int i = 0; i < arrlen(m_renderer_system_data); ++i) {
      RendererData renderer_data = m_renderer_system_data[i]; // NOTE(Vlad): We can sometime don't have any texture or animation, need to handle this too later

      int id = renderer_data.id;
      ImageType image_type = renderer_data.type;

      Box box = m_boxes.Get(id);
      Position position = m_positions.Get(id);
      Program program = m_programs.Get(id);
      Texture texture;

      m_renderer_system->RenderBoxBegin(&position, m_camera_system, &program);

      program.SetUniform1i("u_Texture", 0);

      switch (image_type) {
        case ImageType::ANIMATION: {
          Animation animation = m_animations.Get(id);

          int index = animation.GetIndex();
          texture = m_textures[index];
        }
        break;
        case ImageType::TEXTURE: {
          texture = m_textures[id];   
        }
        break;
      }

      texture.Bind();

      box.Bind();
      box.Draw();
      box.Unbind();

      texture.Unbind();

      m_renderer_system->RenderBoxEnd(&program);
    }
  }
  

  if (m_interface_system->m_render && m_interface_system_id != -1) {
    m_interface_system->m_render(m_interface_system_id); // User code
  }

  double time = GetCounter();
  accumulator += time;
  count++;

  if (count == 500) {
    std::cout << "Render: " << accumulator / count << std::endl;
    accumulator = 0;
    count = 0;
  }
}