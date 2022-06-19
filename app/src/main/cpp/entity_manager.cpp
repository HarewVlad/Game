template <typename T>
void EntityManager::AddComponent(Entity entity, const T &t) {
  T *array = NULL;
  std::type_index type_index = std::type_index(typeid(T));
  if (hmgeti(m_map, type_index) >= 0) {
    array = (T *)hmget(m_map, type_index);
    if (arrlen(array) < entity) {
      arrsetlen(array, arrlen(array) + MIN_ALLOCATION_SIZE);
    }
  } else {
    arrsetlen(array, MIN_ALLOCATION_SIZE);
  }
  arrins(array, entity, t);
  hmput(m_map, type_index, (void *)array);
}

template <typename T>
T *EntityManager::GetComponent(Entity entity) {
  std::type_index type_index = std::type_index(typeid(T));
  if (hmgeti(m_map, type_index) >= 0) {
    T *array = (T *)hmget(m_map, type_index);
    if (arrlen(array) > entity) {
      return &array[entity];
    } else {
      assert(0 && "GetComponent: Wrong entity!");
      return nullptr;
    }
  } else {
    assert(0 && "GetComponent: Wrong type!");
    return nullptr;
  }
}

Entity EntityManager::CreateEntity() {
  return m_entity++;
}