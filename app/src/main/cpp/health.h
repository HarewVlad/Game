struct Health {
  void Initialize(int value);

  int m_value;
};

struct HealthMap {
  int key;
  Health *value;
};