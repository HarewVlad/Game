void InterfaceRenderer::Initialize(ImGuiManager *imgui_manager) {
  m_imgui_manager = imgui_manager;
}

void InterfaceRenderer::Render(EntityManager *entity_manager) {
  assert(arrlen(m_entities) <= 1); // NOTE(Vlad): Currently we only need 1 interface. Need to think about it more.

  for (int i = 0; i < arrlen(m_entities); ++i) {
    Entity entity = m_entities[i];

    m_imgui_manager->RenderBegin();

    ImGuiIO &io = ImGui::GetIO();

    ImGui::SetNextWindowPos(ImVec2(0, 0), 0, ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::SetNextWindowBgAlpha(0);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::Begin("Interface", NULL,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoBringToFrontOnFocus |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoScrollbar);

    if (Global_GameState & GameState_Menu) {
      ImVec2 button_size = {100, 100};
      ImGui::SetCursorPos({io.DisplaySize.x / 2.0f - button_size.x * 0.5f, io.DisplaySize.y / 2.0f - button_size.y * 3});
      if (ImGui::Button("Play", button_size)) {
        Global_GameState = GameState_Run;
      }
      ImGui::SetCursorPosX(io.DisplaySize.x / 2.0f - button_size.x * 0.5f);
      if (ImGui::Button("Reset", button_size)) {
        Global_GameState = GameState_Run;
        Global_GameState |= GameState_Reset;
      }

      ImGui::SetCursorPosX(io.DisplaySize.x / 2.0f - button_size.x * 0.5f);
      ImGui::Button("About", button_size);
      ImGui::SetCursorPosX(io.DisplaySize.x / 2.0f - button_size.x * 0.5f);
      if (ImGui::Button("Exit", button_size)) {
        Global_GameState = GameState_Exit;
      }
    } else if (Global_GameState & GameState_Run) {
      Health *health = entity_manager->GetComponent<Health>(entity);
      Score *score = entity_manager->GetComponent<Score>(entity);
      Stamina *stamina = entity_manager->GetComponent<Stamina>(entity);

      ImGui::Text("Health: %d", health->m_value);
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0, 1.0f, 0, 1));
      ImGui::ProgressBar(stamina->m_value, ImVec2(100.0f, 0.0f));
      ImGui::PopStyleColor();
      ImGui::SetCursorPosX(io.DisplaySize.x / 2);
      ImGui::Text("Score: %d", score->m_value);
    }
    
    ImGui::PopStyleVar(2);
    ImGui::End();

    m_imgui_manager->RenderEnd();
  }
}