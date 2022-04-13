struct CollisionSystem {
  void Initialize();
  void SetOnCollideCallback(const std::function<void(int, int)> on_collide);
  void Update(int id_a, int id_b, Body *body_a, Body *body_b, Movement *movement_a, Movement *movement_b, float dt);
  bool TestAABBAABB(Body *a, Body *b);

  std::function<void(int, int)> m_on_collide;
};

// NOTE(Vlad): "Key" is object that wants to collide with "Value"
struct CollisionMap {
  int key;
  int value;
};