void InterfaceSystem::Initialize(ImGuiManager *imgui_manager) {
  m_imgui_manager = imgui_manager;
}

void InterfaceSystem::SetRender(const std::function<void(int)> render) {
  m_render = render;
}