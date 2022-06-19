// TODO: Later make interface as a component, for example adding healthbars or other interface stuff to enemies or something, to doors objects (opengin interface, ...) and so on

struct InterfaceRenderer : public IRenderer {
  void Initialize(ImGuiManager *imgui_manager);
  void Render(EntityManager *entity_manager) override;

  ImGuiManager *m_imgui_manager;
};