void InterfaceSystem::Initialize(ImGuiManager *imgui_manager) {
  m_imgui_manager = imgui_manager;
}

void InterfaceSystem::SetRender(const std::function<void(int)> render) {
  m_render = render;
}

void InterfaceSystem::Render(int id) {
  m_imgui_manager->RenderBegin();
  if (m_render) m_render(id);
  m_imgui_manager->RenderEnd();
}