struct Physics {
  bool Initialize();
  void Update(Position *position, Movement *movement, float dt);
};

struct PhysicsMap {
  int key;
  Physics *value;
};