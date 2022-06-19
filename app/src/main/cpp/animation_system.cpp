void AnimationSystem::Update(EntityManager *entity_manager, float dt) {
  for (int i = 0; i < arrlen(m_entities); ++i) {
    Entity entity = m_entities[i];

    Animation *animation = entity_manager->GetComponent<Animation>(entity);

    int size = Global_AnimationInfo[animation->m_type].m_size; // TOOD: Change to spritesheet, no need to use this
    if (animation->m_time > 1.0f / size) {
      animation->m_index = (animation->m_index + 1) % size;
      animation->m_time = 0.0f;
    } else {
      animation->m_time += dt;
    }
  }
}