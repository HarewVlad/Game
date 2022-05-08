// enum class ComponentType {
//   BOX,
//   STATE,
//   ANIMATION,
//   PROGRAM,
//   TEXTURE,
//   POSITION,
//   MOVEMENT,
//   BODY,

//   COUNT
// };

// enum class Systems {
//   PHYSICS,
//   CONTROL,
//   CAMERA,
//   COLLISION,
//   RENDERER,
//   FOLLOW,

//   COUNT
// };

template <typename T>
struct Map {
  int key;
  T value;
};

template <typename T>
struct Array {
  // Array() {
  //   m_array = NULL;
  //   m_indexes = NULL;
  //   m_ids = NULL;
  // }

  // void Add(int id, T value) {
  //   if (arrlen(m_indexes) < id) {
  //     arrsetlen(m_indexes, id); // TODO: Make more efficient with allocations
  //   }

  //   arrins(m_indexes, id, arrlen(m_array));
  //   arrput(m_array, value);
  // }

  // void AddReference(int ida, int idb) { // NOTE(Vlad): ida want to stick to idb component
  //   if (arrlen(m_indexes) < ida) {
  //     arrsetlen(m_indexes, ida);
  //   }

  //   arrins(m_indexes, ida, idb);
  // }

  // void Remove(int id) {
  //   int index = m_indexes[id];
  //   arrdel(m_array, index);
  //   arrdel(m_indexes, id);
  // }

  // int GetIndex(int id) {
  //   return m_indexes[id];
  // }

  // T &Get(int id) {
  //   int index = m_indexes[id];
  //   return m_array[index];
  // }

  // int Size() {
  //   return arrlen(m_indexes);
  // }

  // T *m_array;
  // int *m_indexes;
  // int *m_ids;

  Array() {
    m_map = NULL;
  }

  void Add(int id, T value) {
    hmput(m_map, id, value);
  }

  T &Value(int id) {
    return hmget(m_map, id);
  }

  Map<T> &GetPair(int index) {
    return m_map[index];
  }

  int Size() {
    return hmlen(m_map);
  }

  Map<T> *m_map;
};

// #define CREATE_COMPONENT(Type) Array<Type> ##Type##Components;
// #define ADD_COMPONENT(Type, Id, Value) Type##Components.Add(Id, Value);
// #define GET_COMPONENT(Type, Id) Type##Components.Get(Id);

struct EntityManager {
  void Initialize(CameraSystem *camera_system, RendererSystem *renderer_system,
                  PhysicsSystem *physics_system,
                  CollisionSystem *collision_system,
                  FollowSystem *follow_system, ControlSystem *control_system,
                  InterfaceSystem *interface_system);
  void SetEntity(int id);
  void AddAnimation(int id, const Animation &animation); // TODO: Later replace with AnimationRange AddAnimation(...)
  void AddAnimation(const Animation &animation);
  void AddBox(int id, const Box &box); // NOTE(Vlad): But VertexArray is still need to be existent in "main". Later need to copy it in Box structure like we do there
  void AddBox(const Box &box);
  void AddProgram(int id, const Program &program);
  void AddProgram(const Program &program);
  void AddTexture(const Texture &texture);
  Range AddTextures(const char *fmt, int size);
  void AddPosition(int id, const Position &position);
  void AddPosition(const Position &position);
  void AddPositionReference(int ida, int idb);
  void AddMovement(int id, const Movement &movement);
  void AddMovement(const Movement &movement);
  void AddBody(int id, const Body &body);
  void AddBody(const Body &body);

  void AddToPhysics(int id);
  void AddToPhysics();
  void AddToRenderer(int id, ImageType type);
  void AddToRenderer(ImageType type);
  void
  AddToCollision(int a,
                 int b); // NOTE(Vlad) A - Object that wants to collide with B
  void SetToCamera(int id);
  void SetToCamera();
  void SetToControl(int id);
  void SetToControl();
  void SetToInterface(int id);
  void SetToInterface();
  void AddToFollow(int a, int b); // NOTE(Vlad): A - Follower, B - The KING

  void Update(float dt);
  void RenderGame();
  void Render();

  void Old(float dt);

  // Components
  Array<Animation> m_animations;
  Array<Box> m_boxes;
  Array<Program> m_programs;
  Array<Position> m_positions;
  Movement *m_movements;
  Array<Body> m_bodies;
  Texture *m_textures;

  // Test
  void AddBlink(int id, const EffectBlink &effect_blink) {
    m_effect_blinks.Add(id, effect_blink);
  }

  Array<EffectBlink> m_effect_blinks;

  // Systems
  PhysicsSystem *m_physics_system;
  int *m_physics_system_ids;

  RendererSystem *m_renderer_system;
  RendererData *m_renderer_system_data;
  int *m_renderer_system_ids;

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

  int m_id;
};