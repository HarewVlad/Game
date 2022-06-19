// TODO: Works for now, need to change later (May be replace with hashing lol)
enum CollisionGroup_ {
  CollisionGroup_None = 0,
  CollisionGroup_Player = 1 << 0,
  CollisionGroup_Enemy = 1 << 1,
  CollisionGroup_Arena = 1 << 2
};

enum CollisionType_ {
  CollisionType_PlayerEnemy = CollisionGroup_Player | CollisionGroup_Enemy,
  CollisionType_PlayerArena = CollisionGroup_Player | CollisionGroup_Arena,
  CollisionType_EnemyArena = CollisionGroup_Enemy | CollisionGroup_Arena,
};

struct CollisionSystem : public ISystem {
  void Update(EntityManager *entity_manager, float dt) override;
  void AddEntity(Entity entity, int group);
  bool TestAABBAABB(Body *ba, Body *bb, Position *pa, Position *pb);
  bool TestAABBInsideAABB(Body *bounding, Body *internal, Position *bounding_position, Position *inner_position);
  
  int *m_collision_groups = NULL;
};