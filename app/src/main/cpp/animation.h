// TODO: Make it AnimationSystem
struct AnimationMap {
  int key;
  Range value;
};

struct Animation {
  void Initialize();
  void Add(int id, Range range);
  void Update(float dt);
  void SetAnimation(int id);
  int GetIndex();

  AnimationMap *m_animation_map; // TODO: Replace with array?

  int m_id;
  int m_index;
  float m_time;
};
