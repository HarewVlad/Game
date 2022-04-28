enum class ComponentType {
  BOX,
  STATE,
  ANIMATION,
  PROGRAM,
  TEXTURE,
  POSITION,
  MOVEMENT,
  BODY,

  COUNT
};

enum class Systems {
  PHYSICS,
  CONTROL,
  CAMERA,
  COLLISION,
  RENDERER,
  FOLLOW,

  COUNT
};

struct IndexMap {
  int key;
  int value;
};

template <typename T>
struct Component {
  inline void Initialize() {
    m_array = NULL;
    m_indexes = NULL;
  }

  inline void Add(int id, T value) {
    hmput(m_indexes, id, arrlen(m_array));
    arrput(m_array, value);
  }

  inline T &Get(int id) {
    int index = hmget(m_indexes, id);
    return m_array[index];
  }

  T *m_array;
  IndexMap *m_indexes;
};

struct EntityManager {
  void Initialize(CameraSystem *camera_system, RendererSystem *renderer_system,
                  PhysicsSystem *physics_system,
                  CollisionSystem *collision_system,
                  FollowSystem *follow_system, ControlSystem *control_system,
                  InterfaceSystem *interface_system);
  void AddAnimation(int id, Animation animation);
  void AddBox(int id, Box box); // NOTE(Vlad): But VertexArray is still need to be existent in "main". Later need to copy it in Box structure like we do there
  void AddProgram(int id, Program program);
  void AddTexture(int id, Texture texture);
  void AddPosition(int id, Position position);
  void AddMovement(int id, Movement movement);
  void AddBody(int id, Body body);
  void AddState(int id, State state);
  void AddHealth(int id, Health health);

  void AddToPhysics(int id);
  void AddToRenderer(int id, ImageType type);
  void
  AddToCollision(int a,
                 int b); // NOTE(Vlad) A - Object that wants to collide with B
  void SetToCamera(int id);
  void SetToControl(int id);
  void SetToInterface(int id);
  void AddToFollow(int a, int b); // NOTE(Vlad): A - Follower, B - The KING

  void RemoveFromCollision(int id);
  void RemoveFromPhysics(int id);
  void RemoveFromControl(int id);

  void Update(float dt);
  void Render();

  void Old(float dt);

  // Components
  Component<Animation> m_animations;
  Component<Box> m_boxes;
  Component<Program> m_programs;
  Component<Texture> m_textures;
  Component<Position> m_positions;
  Movement *m_movements;
  Component<Body> m_bodies;
  Component<State> m_states;
  Component<Health> m_healths;

  // TODO: Add ability to add custom components


  // Systems
  PhysicsSystem *m_physics_system;
  int *m_physics_system_ids;

  RendererSystem *m_renderer_system;
  RendererData *m_renderer_system_data;

  CollisionSystem *m_collision_system;
  CollisionPair *m_collision_pairs;

  CameraSystem *m_camera_system;
  int m_camera_system_id; // NOTE(Vlad): Only one entity can use camera

  FollowSystem *m_follow_system;
  FollowMap *m_follow_map;

  ControlSystem *m_control_system;
  int m_control_system_id; // NOTE(Vlad): Only one can be controlled for now

  InterfaceSystem *m_interface_system;
  int m_interface_system_id;

  // TODO: Add ability to add custom systems
};

// map<int, array()