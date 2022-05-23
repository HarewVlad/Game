struct FollowSystem {
  void Initialize(WindowManager *window_manager); // NOTE(Vlad): "a" follows "b"
  void Update(Position *a, Position *b);
  void Update(glm::vec2 &a, Position *b); // NOTE(Vlad): For camera

  WindowManager *m_window_manager;
};

// NOTE(Vlad): Key - Follower, Value - Dungeon Master
struct FollowMap {
  int key;
  int value;
};