// TODO: Later make interface as a component, for example adding healthbars or other interface stuff to enemies or something, to doors objects (opengin interface, ...) and so on

struct InterfaceSystem {
  void Initialize(ImGuiManager *imgui_manager);
  void SetRender(const std::function<void(int)> render);

  ImGuiManager *m_imgui_manager;
  std::function<void(int)> m_render;
};