struct CollisionSystem {
  bool Initialize();
  void Update(AABB *a, AABB *b, float dt);
  bool TestAABBAABB(AABB *a, AABB *b);
};