struct InterfaceSystem {
  void Initialize(ImGuiManager *imgui_manager);
  void Render();
  void Update(float dt) // TODO: Make user define what components he needs, just pass id later

  ImGuiManager *m_imgui_manager;
};