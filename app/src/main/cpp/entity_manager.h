struct EntityManager {
  bool Initialize(CameraSystem *camera_system, RendererSystem *renderer_system, PhysicsSystem *physics_system, CollisionSystem *collision_system, FollowSystem *follow_system);
  void AddControl(int id, Control *control);
  void AddAnimation(int id, Animation *animation);
  void AddBox(int id, Box *box);
  void AddProgram(int id, Program *program);
  void AddTexture(int id, Texture *texture);
  void AddPosition(int id, Position *position);
  void AddMovement(int id, Movement *movement);
  void AddState(int id, State *state);
  void AddBody(int id, Body *body);

  void AddToPhysics(int id);
  void AddToRenderer(int id);
  void AddToCollision(int id);
  void SetToCamera(int id);
  void AddToFollow(int a, int b); // NOTE(Vlad): 1 object follows the center of the other object

  void Update(float dt);
  void Render();

  // Components
  ControlMap *m_controls;
  AnimationMap *m_animations;
  BoxMap *m_boxes;
  ProgramMap *m_programs;
  TextureMap *m_textures;
  PositionMap *m_positions;
  MovementMap *m_movements;
  BodyMap *m_bodies;
  StateMap *m_states;

  // Systems
  PhysicsSystem *m_physics_system;
  int *m_physics_system_ids;

  RendererSystem *m_renderer_system;
  int *m_renderer_system_ids;

  CollisionSystem *m_collision_system;
  int *m_collision_system_ids;

  CameraSystem *m_camera_system;
  int m_camera_system_id; // NOTE(Vlad): Only one entity can use camera

  FollowSystem *m_follow_system;
  FollowMap *m_follow_map;
};