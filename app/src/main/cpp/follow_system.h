struct FollowSystem {
  void Initialize(GLFWManager *glfw_manager); // NOTE(Vlad): "a" follows "b"
  inline void Update(Position *a, Position *b);

  GLFWManager *m_glfw_manager;
};

// NOTE(Vlad): Key - Follower, Value - Dungeon Master
struct FollowMap {
  int key;
  int value;
};