struct State {
  void Initialize(int value);

  int m_value;
};

struct StateMap {
  int key;
  State *value;
};