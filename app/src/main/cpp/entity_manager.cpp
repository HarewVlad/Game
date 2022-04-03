// TODO: Add warnings when Texture and Animation bound at the same time (Static vs. Dynamic)
// TODO: What if two Entities have the same Physics component, why need to store it twice? Fix it dude

bool EntityManager::Initialize() {
  m_controls = NULL;
  m_animations = NULL;
  m_cameras = NULL;
  m_boxes = NULL;
  m_renderers = NULL;
  m_programs = NULL;
  m_textures = NULL;
  m_positions = NULL;
  m_movements = NULL;
  m_physics = NULL;
  
  return true;
}

void EntityManager::AddRenderer(int id, Renderer *renderer) {
  hmput(m_renderers, id, renderer);
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

void EntityManager::AddBox(int id, Box *box) {
  hmput(m_boxes, id, box);
}

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

void EntityManager::AddPhysics(int id, Physics *physics) {
  hmput(m_physics, id, physics);
}

void EntityManager::Update(float dt) {
  for (int i = 0; i < hmlen(m_physics); ++i) {
    Position *position = hmget(m_positions, m_physics[i].key);
    Movement *movement = hmget(m_movements, m_physics[i].key);

    m_physics[i].value->Update(position, movement, dt);
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
  for (int i = 0; i < hmlen(m_renderers); ++i) {
    Box *box = hmget(m_boxes, i);
    Position *position = hmget(m_positions, i);
    Animation *animation = hmget(m_animations, i);
    Renderer *renderer = hmget(m_renderers, i);
    Camera *camera = hmget(m_cameras, i);
    Program *program = hmget(m_programs, i);
    Texture *texture = hmget(m_textures, i);

    renderer->RenderBoxBegin(position, camera, program);

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

    renderer->RenderBoxEnd(program);
  }
}