bool EntityManager::Initialize() {
  m_controls = NULL;
  m_animations = NULL;
  return true;
}

void EntityManager::AddAnimation(Animation *animation) {
  arrput(m_animations, animation);
}

void EntityManager::AddControl(Control *control) {
  arrput(m_controls, control);
}

void EntityManager::Update(float dt) {
  for (int i = 0; i < arrlen(m_controls); ++i) {
    m_controls[i]->Update(dt);
  }

  for (int i = 0; i < arrlen(m_animations); ++i) {
    m_animations[i]->Update(dt);
  }
}