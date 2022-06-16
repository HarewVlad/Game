struct Engine {
  void Initialize(PlatformManager *platform_manager, AssetManager *asset_manager);
  void Script();
  void Loop();
  void Render();
  void Update(float dt);
  template <typename T>
  void AddSystem(ISystem *system);
  template <typename T>
  T *GetSystem();
  template <typename T>
  void AddRenderer(IRenderer *renderer);
  template <typename T>
  T *GetRenderer();

  // Essentials
  PlatformManager *m_platform_manager;
  AssetManager *m_asset_manager;

  // Entity manager
  EntityManager m_entity_manager;

  // Systems
  Map<std::type_index, ISystem *> *m_systems = NULL;
  Map<std::type_index, IRenderer *> *m_renderers = NULL; // NOTE(Vlad): Mb do something else
};