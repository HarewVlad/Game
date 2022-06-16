// TODO: Create system like Animation that contains size and 

void AnimationSystem::Update(EntityManager *entity_manager, float dt) {
  for (int i = 0; i < arrlen(m_entities); ++i) {
    Entity entity = m_entities[i];

    Animation *animation = entity_manager->GetComponent<Animation>(entity); // For each entity

    int size = Global_AnimationInfo[animation->m_type].m_size;
    if (animation->m_time > 1.0f / size) {
      animation->m_index = (animation->m_index + 1) % size;
      animation->m_time = 0.0f;
    } else {
      animation->m_time += dt;
    }
  }
}