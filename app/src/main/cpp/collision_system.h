struct CollisionSystem {
  bool Initialize();
  void Update(Body *a, Body *b, Movement *c, Movement *d, float dt);
  bool TestAABBAABB(Body *a, Body *b);
};