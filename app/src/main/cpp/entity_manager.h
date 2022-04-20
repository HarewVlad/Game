enum class Components {
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

struct ComponentMap {
  int key;
  void *value;
};

struct Component {
  int key;
  ComponentMap *value;
};

struct EntityManager {
  void Initialize(CameraSystem *camera_system, RendererSystem *renderer_system,
                  PhysicsSystem *physics_system,
                  CollisionSystem *collision_system,
                  FollowSystem *follow_system, ControlSystem *control_system,
                  InterfaceSystem *interface_system);
  void AddAnimation(int id, Animation *animation);
  void AddBox(int id, Box *box);
  void AddProgram(int id, Program *program);
  void AddTexture(int id, Texture *texture);
  void AddPosition(int id, Position *position);
  void AddMovement(int id, Movement *movement);
  void AddBody(int id, Body *body);
  void AddState(int id, State *state);
  void AddHealth(int id, Health *health);

  void AddToPhysics(int id);
  void AddToRenderer(int id);
  void
  AddToCollision(int a,
                 int b); // NOTE(Vlad) A - Object that wants to collide with B
  void SetToCamera(int id);
  void SetToControl(int id);
  void SetToInterface(int id);
  void AddToFollow(int a, int b); // NOTE(Vlad): A - Follower, B - The KING

  void RemoveFromCollision(int id);
  void RemoveFromPhysics(int id);
  void RemoveFromRender(int id);
  void RemoveFromControl(int id);

  void Update(float dt);
  void Render();

  void AddComponent(int id, int type, void *data) {
    // std::map<type, std::map<entity, type>>
    ComponentMap *component_map = NULL;
    if (hmgeti(m_components, type) >= 0) { // If component registered
      component_map = hmget(m_components, type);
      hmput(component_map, id, data);
    } else {
      hmput(component_map, id, data);
    }
    hmput(m_components, type, component_map);
  }

  void *GetComponent(int type, int id) {
    if (hmgeti(m_components, type) >= 0) {
      ComponentMap *component_map = m_components[type].value;
      return component_map[id].value;
    } else {
      return NULL;
    }
  }

  void Old(float dt);
  void New(float dt);

  // Components
  AnimationMap *m_animations;
  BoxMap *m_boxes;
  ProgramMap *m_programs;
  TextureMap *m_textures;
  PositionMap *m_positions;
  MovementMap *m_movements;
  BodyMap *m_bodies;
  StateMap *m_states;
  HealthMap *m_healths;

  // Systems
  PhysicsSystem *m_physics_system;
  int *m_physics_system_ids;

  RendererSystem *m_renderer_system;
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

  // Test
  Component *m_components;
};

// map<int, array()