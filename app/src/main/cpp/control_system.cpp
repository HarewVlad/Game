void ControlSystem::Update(EntityManager *entity_manager, float dt) {
  assert(arrlen(m_entities) <= 1);

#ifdef _WIN32
  for (int i = 0; i < arrlen(m_entities); ++i) {
    Entity entity = m_entities[i];

    Movement *movement = entity_manager->GetComponent<Movement>(entity);
    Box *box = entity_manager->GetComponent<Box>(entity);
    Animation *animation = entity_manager->GetComponent<Animation>(entity);
    Stamina *stamina = entity_manager->GetComponent<Stamina>(entity);

    if (ImGui::IsKeyDown(GLFW_KEY_A)) {
      if (ImGui::IsKeyDown(GLFW_KEY_LEFT_SHIFT) && stamina->m_value > 0) {
        movement->m_force.x -= 4000.0f;
        stamina->m_value -= dt * 0.5f;
      } else {
        if (stamina->m_value < 1)
          stamina->m_value += dt * 0.1f;
      }

      movement->m_velocity.x -= 40.0f;
      animation->Set(AnimationType_PlayerRun);
      // box->m_vertex_buffer.BindData(&player_vertices_flipped, sizeof(player_vertices_flipped));
    } else if (ImGui::IsKeyDown(GLFW_KEY_D)) {
      if (ImGui::IsKeyDown(GLFW_KEY_LEFT_SHIFT) && stamina->m_value > 0) {
        movement->m_force.x += 4000.0f;
        stamina->m_value -= dt * 0.5f;
      } else {
        if (stamina->m_value < 1)
          stamina->m_value += dt * 0.1f;
      }

      movement->m_velocity.x += 40.0f;
      animation->Set(AnimationType_PlayerRun);
      // box->m_vertex_buffer.BindData(&player_vertices, sizeof(player_vertices));
    }
    else {
      animation->Set(AnimationType_PlayerIdle);
      if (stamina->m_value < 1)
        stamina->m_value += dt * 0.1f;
    }
  }

  if (ImGui::IsKeyDown(GLFW_KEY_ESCAPE)) {
    Global_GameState = GameState_Menu;
  }
#elif defined __ANDROID__

#endif
}