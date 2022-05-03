// TODO: Make it AnimationSystem and take just sprites and ids

struct Range {
  int m_start;
  int m_end;
};

struct AnimationMap {
  int key;
  Range value;
};

struct Animation {
  void Initialize();
  void Add(int id, Range range);
  inline void Update(float dt);
  inline void SetAnimation(int id);
  inline int GetIndex();

  AnimationMap *m_animation_map;

  int m_id;
  int m_index;
  float m_time;
};
