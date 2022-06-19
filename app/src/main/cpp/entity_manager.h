template <typename T, typename V>
struct Map {
  T key;
  V value;
};

template <typename T>
struct Array {
  T *Get(int index) { return &data[index]; }

  T *data;
};

typedef int Entity;

struct EntityManager {
  Entity CreateEntity();

  template <typename T>
  void AddComponent(Entity entity, const T &t);

  template <typename T>
  T *GetComponent(Entity entity);

  Map<std::type_index, void *> *m_map = NULL;
  Entity m_entity = 0;
};