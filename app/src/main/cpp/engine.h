struct Engine {
  void Initialize(WindowManager *window_manager, ImGuiManager *imgui_manager, PathManager *path_manager, InputManager *input_manager);
  void Start();
  void Loop();
  void Render();
  void Update(float dt);

  // Essentials
  InputManager *m_input_manager;
  WindowManager *m_window_manager;
  ImGuiManager *m_imgui_manager;
  PathManager *m_path_manager;

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
};