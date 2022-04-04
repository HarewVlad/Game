// TODO: Add warnings when Texture and Animation bound at the same time (Static
// vs. Dynamic)
// TODO: What if two Entities have the same Physics component, why need to store
// it twice? Fix it dude

bool EntityManager::Initialize(RendererSystem *renderer_system,
                               PhysicsSystem *physics_system, CollisionSystem *collision_system) {
  m_controls = NULL;
  m_animations = NULL;
  m_cameras = NULL;
  m_boxes = NULL;
  m_programs = NULL;
  m_textures = NULL;
  m_positions = NULL;
  m_movements = NULL;
  m_aabbs = NULL;
  m_physics_system = physics_system;
  m_physics_system_ids = NULL;
  m_renderer_system = renderer_system;
  m_renderer_system_ids = NULL;
  m_collision_system = collision_system;
  m_collision_system_ids = NULL;

  return true;
}

void EntityManager::AddAnimation(int id, Animation *animation) {
  hmput(m_animations, id, animation);
}

void EntityManager::AddControl(int id, Control *control) {
  hmput(m_controls, id, control);
}

void EntityManager::AddCamera(int id, Camera *camera) {
  hmput(m_cameras, id, camera);
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

void EntityManager::AddState(int id, State *state) {
  hmput(m_states, id, state);
}

void EntityManager::AddAABB(int id, AABB *aabb) {
  hmput(m_aabbs, id, aabb);
}

void EntityManager::AddToPhysics(int id) { arrput(m_physics_system_ids, id); }

void EntityManager::AddToRenderer(int id) { arrput(m_renderer_system_ids, id); }

void EntityManager::AddToCollision(int id) { arrput(m_collision_system_ids, id); }

void EntityManager::Update(float dt) {
  for (int i = 0; i < arrlen(m_physics_system_ids); ++i) {
    Movement *movement = hmget(m_movements, m_physics_system_ids[i]);

    m_physics_system->Update(movement, dt);
  }

  for (int i = 0; i < hmlen(m_movements); ++i) {
    Position *position = hmget(m_positions, m_movements[i].key);

    m_movements[i].value->Update(position, dt);
  }

  for (int i = 0; i < arrlen(m_collision_system_ids); ++i) {
    for (int j = i + 1; j < arrlen(m_collision_system_ids); ++j) {
      AABB *a = hmget(m_aabbs, m_collision_system_ids[i]);
      AABB *b = hmget(m_aabbs, m_collision_system_ids[j]);

      m_collision_system->Update(a, b, dt);
    }
  }

  for (int i = 0; i < hmlen(m_controls); ++i) {
    Movement *movement = hmget(m_movements, m_controls[i].key);

    m_controls[i].value->Update(movement, dt);
  }

  for (int i = 0; i < hmlen(m_cameras); ++i) {
    m_cameras[i].value->Update(dt);
  }

  for (int i = 0; i < hmlen(m_animations); ++i) {
    m_animations[i].value->Update(dt);
  }
}

void EntityManager::Render() {
  for (int i = 0; i < arrlen(m_renderer_system_ids); ++i) {
    int id = m_renderer_system_ids[i];

    Box *box = hmget(m_boxes, id);
    Position *position = hmget(m_positions, id);
    Animation *animation = hmget(m_animations, id);
    Camera *camera = hmget(m_cameras, id);
    Program *program = hmget(m_programs, id);
    Texture *texture = hmget(m_textures, id);

    m_renderer_system->RenderBoxBegin(position, camera, program);

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