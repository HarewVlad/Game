// Todo: Collision system is just straight garbage suitable for the game i making, but in future steal something smart

struct CollisionSystem {
  void Initialize();
  void SetOnNormalCollision(const std::function<void(int, int)> on_collide);
  void SetOnBoundingCollision(const std::function<void(int)> on_collide);
  void Update(int id_a, int id_b, Body *body_a, Body *body_b, Movement *movement_a, Movement *movement_b, float dt);
  bool TestAABBAABB(Body *a, Body *b);
  bool TestAABBInsideAABB(Body *bounding, Body *internal);

  std::function<void(int, int)> m_on_collide_normal;
  std::function<void(int)> m_on_collide_bounding;
};

// NOTE(Vlad): "A" is object that wants to collide with "B"
struct CollisionPair {
  int a;
  int b;
};