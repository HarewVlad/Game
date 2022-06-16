void EnemyResetSystem::Update(EntityManager *entity_manager, float dt) {
  if (!(Global_GameState & GameState_EnemyReset)) {
    return;
  }

  for (int i = 0; i < arrlen(m_entities); ++i) {
    Entity entity = m_entities[i];

    Position *position = entity_manager->GetComponent<Position>(entity);
    position->m_xy = {};

    Movement *movement = entity_manager->GetComponent<Movement>(entity);
    movement->m_velocity = {};
    movement->m_acceleration = {};
  }

  Global_GameState ^= GameState_EnemyReset;
}