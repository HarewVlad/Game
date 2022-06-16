void PlayerResetSystem::Update(EntityManager *entity_manager, float dt) {
  assert(arrlen(m_entities) <= 1); // NOTE(Vlad): Only for one entity, which is player

  if (!(Global_GameState & GameState_PlayerReset)) {
    return;
  }

  for (int i = 0; i < arrlen(m_entities); ++i) {
    Entity entity = m_entities[i];

    Health *health = entity_manager->GetComponent<Health>(entity);
    Score *score = entity_manager->GetComponent<Score>(entity);
    Stamina *stamina = entity_manager->GetComponent<Stamina>(entity);

    health->m_value = 3;
    score->m_value = 0;
    stamina->m_value = 1.0f;
  }
  
  Global_GameState ^= GameState_PlayerReset;
}