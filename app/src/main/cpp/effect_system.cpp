void EffectSystem::Update(EntityManager *entity_manager, float dt) {
  for (int i = 0; i < arrlen(m_entities); ++i) {
    Entity entity = m_entities[i];

    Effect *effect = entity_manager->GetComponent<Effect>(entity);

    int effect_type = m_effect_types[i];
    switch (effect_type) {
      case EffectType_Blink: {
        RenderInfo *render_info = entity_manager->GetComponent<RenderInfo>(entity);

        if (effect->m_total_time < effect->m_duration) {
          if (effect->m_time > 1 / effect->m_frequency) {
            render_info->m_draw ^= 1;
            effect->m_time = 0;
          } else {
            effect->m_time += dt;
            effect->m_total_time += dt;
          }
        } else {
          render_info->m_draw = 1;
        }
      }
      break;
      default:
      break;
    }
  }
}

void EffectSystem::AddEntity(Entity entity, int type) {
  ISystem::AddEntity(entity);
  arrput(m_effect_types, type);
}