struct Game {
  void Initialize();
  void Start();

  // Essentials
  GLFWManager m_glfw_manager;
  ImGuiManagerWin32 m_imgui_manager;

  // Systems
  CameraSystem m_camera_system;
  RendererSystem m_renderer_system;
  PhysicsSystem m_physics_system;
  CollisionSystem m_collision_system;
  FollowSystem m_follow_system;
  ControlSystem m_control_system;
  InterfaceSystem m_interface_system;

  // Entity manager
  EntityManager m_entity_manager;

  // Game loop
  Win32Manager m_win32_manager;
};