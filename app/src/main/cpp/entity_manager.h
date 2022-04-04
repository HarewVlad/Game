struct EntityManager {
  bool Initialize(RendererSystem *renderer_system, PhysicsSystem *physics_system, CollisionSystem *collision_system);
  void AddControl(int id, Control *control);
  void AddAnimation(int id, Animation *animation);
  void AddCamera(int id, Camera *camera);
  void AddBox(int id, Box *box);
  void AddProgram(int id, Program *program);
  void AddTexture(int id, Texture *texture);
  void AddPosition(int id, Position *position);
  void AddMovement(int id, Movement *movement);
  void AddState(int id, State *state);
  void AddAABB(int id, AABB *aabb);

  void AddToPhysics(int id);
  void AddToRenderer(int id);
  void AddToCollision(int id);

  void Update(float dt);
  void Render();

  // Components
  ControlMap *m_controls;
  AnimationMap *m_animations;
  CameraMap *m_cameras;
  BoxMap *m_boxes;
  ProgramMap *m_programs;
  TextureMap *m_textures;
  PositionMap *m_positions;
  MovementMap *m_movements;
  AABBMap *m_aabbs;
  StateMap *m_states;

  // Systems
  PhysicsSystem *m_physics_system;
  int *m_physics_system_ids;

  RendererSystem *m_renderer_system;
  int *m_renderer_system_ids;

  CollisionSystem *m_collision_system;
  int *m_collision_system_ids;
};