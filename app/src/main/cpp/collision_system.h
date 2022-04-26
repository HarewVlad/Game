// Todo: Collision system is just straight garbage suitable for the game i making, but in future steal something smart

struct CollisionSystem {
  void Initialize();
  void SetOnNormalCollision(const std::function<void(int, int)> on_collide);
  void SetOnBoundingCollision(const std::function<void(int)> on_collide);
  inline void Update(int ida, int idb, Body *ba, Body *bb, Position *pa, Position *pb, float dt);
  inline bool TestAABBAABB(Body *a, Body *b, Position *pa, Position *pb);
  inline bool TestAABBInsideAABB(Body *bounding, Body *internal, Position *bounding_position, Position *inner_position);

  std::function<void(int, int)> m_on_collide_normal;
  std::function<void(int)> m_on_collide_bounding;
};

// NOTE(Vlad): "A" is object that wants to collide with "B"
struct CollisionPair {
  int a;
  int b;
};