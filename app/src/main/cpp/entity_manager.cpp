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
  m_textures = NULL;
}

void EntityManager::SetEntity(int id) {
  m_id = id;
}

void EntityManager::AddAnimation(int id, const Animation &animation) {
  m_animations.Add(id, animation);
}

void EntityManager::AddBox(int id, const Box &box) {
  m_boxes.Add(id, box);
}

void EntityManager::AddProgram(int id, const Program &program) {
  m_programs.Add(id, program);
}

void EntityManager::AddTexture(const Texture &texture) {
  arrput(m_textures, texture);
}

void EntityManager::AddPosition(int id, const Position &position) {
  m_positions.Add(id, position);
}

void EntityManager::AddPositionReference(int ida, int idb) {
  // m_positions.AddReference(ida, idb);
}

void EntityManager::AddMovement(int id, const Movement &movement) {
  if (id >= arrlen(m_movements)) {
    arrsetlen(m_movements, id);
  }
  arrins(m_movements, id, movement);
}

void EntityManager::AddBody(int id, const Body &body) {
  m_bodies.Add(id, body);
}

void EntityManager::AddAnimation(const Animation &animation) {
  AddAnimation(m_id, animation);
}

void EntityManager::AddBox(const Box &box) {
  AddBox(m_id, box);
}

void EntityManager::AddProgram(const Program &program) {
  AddProgram(m_id, program);
}

void EntityManager::AddPosition(const Position &position) {
  AddPosition(m_id, position);
}

void EntityManager::AddMovement(const Movement &movement) {
  AddMovement(m_id, movement);
}

void EntityManager::AddBody(const Body &body) {
  AddBody(m_id, body);
}

void EntityManager::SetToCamera(int id) { m_camera_system_id = id; }

void EntityManager::SetToControl(int id) { m_control_system_id = id; }

void EntityManager::SetToInterface(int id) {
  m_interface_system_id = id;
}

void EntityManager::AddToPhysics(int id) { arrput(m_physics_system_ids, id); }

void EntityManager::AddToRenderer(int id, ImageType type) {
  RendererData data = {type};
  arrput(m_renderer_system_data, data);
  arrput(m_renderer_system_ids, 1);
}

void EntityManager::AddToCollision(int a, int b) {
  CollisionPair pair = {a, b};
  arrput(m_collision_pairs, pair);
}

void EntityManager::AddToFollow(int a, int b) { hmput(m_follow_map, a, b); }

Range EntityManager::AddTextures(Texture *textures, int size) {
  Range result = {(int)arrlen(m_textures), (int)(arrlen(m_textures) + size)};

  for (int i = 0; i < size; ++i) {
    AddTexture(textures[i]);
  }

  return result;
}

void EntityManager::AddToPhysics() {
  AddToPhysics(m_id);
}

void EntityManager::AddToRenderer(ImageType type) {
  AddToRenderer(m_id, type);
}

void EntityManager::SetToCamera() {
  SetToCamera(m_id);
}

void EntityManager::SetToControl() {
  SetToControl(m_id);
}

void EntityManager::SetToInterface() {
  SetToInterface(m_id);
}

void EntityManager::Update(float dt) {
  if (Global_GameState != GameState::RUN) {
    return;
  }

  for (int i = 0; i < arrlen(m_movements); ++i) {
    Position &position = m_positions.Value(i);

    m_movements[i].Update(&position, dt); // TODO: Add Physics component instead of this, and make MovementSystem
  }

  for (int i = 0; i < m_animations.Size(); ++i) {
    m_animations.Value(i).Update(dt);
  }

  // Effects
  for (int i = 0; i < m_effect_blinks.Size(); ++i) {
    auto &pair = m_effect_blinks.GetPair(i);
    pair.value.Update(&m_renderer_system_ids[pair.key], dt);
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
    Body &ba = m_bodies.Value(ida);
    Body &bb = m_bodies.Value(idb);
    Position &pa = m_positions.Value(ida);
    Position &pb = m_positions.Value(idb);

    m_collision_system->Update(ida, idb, &ba, &bb, &pa,
                               &pb, dt);
  }

  for (int i = 0; i < hmlen(m_follow_map); ++i) {
    Position &a = m_positions.Value(m_follow_map[i].key);
    Position &b = m_positions.Value(m_follow_map[i].value);

    m_follow_system->Update(&a, &b);
  }

  if (m_camera_system_id != -1) {
    Position &b = m_positions.Value(m_camera_system_id);

    m_follow_system->Update(m_camera_system->m_xy, &b);
  }
}

void EntityManager::RenderGame() {
  for (int id = 0; id < arrlen(m_renderer_system_ids); ++id) {
    if (!m_renderer_system_ids[id]) {
      continue;
    }

    const RendererData renderer_data = m_renderer_system_data[id];
    ImageType image_type = renderer_data.type;

    Box &box = m_boxes.Value(id);
    const Position &position = m_positions.Value(id);
    Program &program = m_programs.Value(id);
    Texture texture;

    const glm::mat4 mv = m_camera_system->GetView() * position.GetModel();

    m_renderer_system->RenderBoxBegin(&program, mv);

    program.SetUniform1i("u_Texture", 0);

    switch (image_type) {
      case ImageType::ANIMATION: {
        Animation animation = m_animations.Value(id);

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

void EntityManager::Render() {
  if (Global_GameState == GameState::RUN) {
    RenderGame();
  }

  m_interface_system->Render(m_interface_system_id);
}