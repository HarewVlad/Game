struct FollowSystem {
  void Initialize(Size *window_size); // NOTE(Vlad): "a" follows "b"
  void Update(Position *a, Position *b);
  void Update(glm::vec2 &a, Position *b); // NOTE(Vlad): For camera

  Size *m_window_size;
};

// NOTE(Vlad): Key - Follower, Value - Dungeon Master
struct FollowMap {
  int key;
  int value;
};