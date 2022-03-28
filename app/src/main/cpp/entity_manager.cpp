bool EntityManager::Initialize() {
  m_input_entities = NULL;
  m_animation_entities = NULL;
  return true;
}

void EntityManager::AddInput(int id, Box *box, Input *input) {
  EntityInput entity_input;
  entity_input.Initialize(box, input);

  hmput(m_input_entities, id, entity_input);
}

void EntityManager::AddAnimation(int id, Animation *animation) {
  EntityAnimation entity_animation;
  entity_animation.Initialize(animation);

  hmput(m_animation_entities, id, entity_animation);
}

void EntityManager::Update(float dt) {
  for (int i = 0; i < hmlen(m_input_entities); ++i) {
    auto &entity = m_input_entities[i].value;

    entity.Update(dt);
  }

  for (int i = 0; i < hmlen(m_animation_entities); ++i) {
    auto &entity = m_animation_entities[i].value;

    entity.Update(dt);
  }
}