void MovementSystem::Update(EntityManager *entity_manager, float dt) {
  for (int i = 0; i < arrlen(m_entities); ++i) {
    Entity entity = m_entities[i];

    Position *position = entity_manager->GetComponent<Position>(entity);
    Movement *movement = entity_manager->GetComponent<Movement>(entity);

    position->m_xy += movement->m_velocity * dt;

    const glm::vec2 acceleration = movement->m_acceleration + movement->m_force * movement->m_imass;

    movement->m_velocity += acceleration * dt;
    movement->m_velocity *= powf(movement->m_damping, dt);
    movement->m_force = {};
  }
}