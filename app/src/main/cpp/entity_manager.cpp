// TODO: Change structure to DOTS ECS later someday may be
// TODO: Add warnings when Texture and Animation bound at the same time (Static vs. Dynamic)

bool EntityManager::Initialize() {
  m_controls = NULL;
  m_animations = NULL;
  m_cameras = NULL;
  m_boxes = NULL;
  m_renderers = NULL;
  m_programs = NULL;
  m_textures = NULL;
  
  return true;
}

void EntityManager::AddRenderer(Entity id, Renderer *renderer) {
  hmput(m_renderers, id, renderer);
}

void EntityManager::AddAnimation(Entity id, Animation *animation) {
  hmput(m_animations, id, animation);
}

void EntityManager::AddControl(Entity id, Control *control) {
  hmput(m_controls, id, control);
}

void EntityManager::AddCamera(Entity id, Camera *camera) {
  hmput(m_cameras, id, camera);
}

void EntityManager::AddBox(Entity id, Box *box) {
  hmput(m_boxes, id, box);
}

void EntityManager::AddProgram(Entity id, Program *program) {
  hmput(m_programs, id, program);
}

void EntityManager::AddTexture(Entity id, Texture *texture) {
  hmput(m_textures, id, texture);
}

void EntityManager::Update(float dt) {
  for (int i = 0; i < hmlen(m_controls); ++i) {
    Box *box = hmget(m_boxes, i); // NOTE(Vlad): Check whether box present or not

    m_controls[i].value->Update(box, dt);
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
    Animation *animation = hmget(m_animations, i);
    Renderer *renderer = hmget(m_renderers, i);
    Camera *camera = hmget(m_cameras, i);
    Program *program = hmget(m_programs, i);
    Texture *texture = hmget(m_textures, i);

    renderer->RenderBoxBegin(box, camera, program);

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