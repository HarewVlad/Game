#include <vector>
#include <typeinfo>
#include <typeindex>
#include <assert.h>

namespace Tests {

typedef int Entity;

template <typename K, typename V>
struct Map {
  K key;
  V value;
};

struct Position {
  int x, y;
};

struct Movement {
  int x, y;
};

struct Animation {
  int x, y;
};

template <typename ...T>
struct EntityArchetype {
  EntityArchetype(): m_type_indexes{std::type_index(typeid(T))...} {
    
  }

  std::vector<std::type_index> m_type_indexes;
};

// TODO: Add global component
struct EntityManager {
  template <typename T>
  void AddComponent(Entity entity, const T &t) {
    std::type_index type_index = std::type_index(typeid(T));
    if (hmgeti(m_components, type_index) >= 0) {
      T *array = (T *)hmget(m_components, type_index);
      if (arrlen(array) < entity) {
        arrsetlen(array, arrlen(array) + 128);
      }
      arrins(array, entity, t);
    } else {
      T *array = NULL;
      arrsetlen(array, 128);
      arrins(array, entity, t);
      hmput(m_components, type_index, (void *)array);
    }
  }

  Entity CreateEntity() {
    return m_entity++;
  }

  // void AddComponent(const EntityArchetype<> &entity_archetype) {
  //   for (int i = 0; i < entity_archetype.m_type_indexes.size(); ++i) {

  //   }
  // }

  template <typename T>
  T *GetComponent(Entity entity) {
    std::type_index type_index = std::type_index(typeid(T));
    if (hmgeti(m_components, type_index) >= 0) {
      T *array = (T *)hmget(m_components, type_index);
      return &array[entity];
    } else {
      assert(0, "Component of that type and ID doesn't exist!");
    }
  }

  Map<std::type_index, void *> *m_components = NULL;
  Entity m_entity = 0;
};

struct ISystem {
  virtual void Update(EntityManager *entity_manager, float dt) = 0;
  void AddEntity(Entity entity) {
    arrput(m_entities, entity);
  }

  Entity *m_entities = NULL;
};

struct MovementSystem : public ISystem {
  void Update(EntityManager *entity_manager, float dt) override {
    for (int i = 0; i < arrlen(m_entities); ++i) {
      Entity entity = m_entities[i];

      Position *position = entity_manager->GetComponent<Position>(entity);
      Movement *movement = entity_manager->GetComponent<Movement>(entity);

      int a = 10;
    }
  }
};

struct CustomSystem : public ISystem {
  void Update(EntityManager *entity_manager, float dt) override {
    for (int i = 0; i < arrlen(m_entities); ++i) {
      Entity entity = m_entities[i];

      Animation *animation = entity_manager->GetComponent<Animation>(entity);

      int a = 10;
    }
  }
};

struct Engine {
  template <typename T>
  void AddSystem(ISystem *system) {
    std::type_index type_index = std::type_index(typeid(T));
    hmput(m_systems, type_index, system);
  }

  void Run(float dt) {
    for (int i = 0; i < hmlen(m_systems); ++i) {
      m_systems[i].value->Update(&m_entity_manager, dt);
    }
  }

  template <typename T>
  T *GetSystem() {
    std::type_index type_index = std::type_index(typeid(T));
    return (T *)hmget(m_systems, type_index);
  }

  // NOTE(Vlad): Were we are creating game
  void Script() {
    Entity entity = m_entity_manager.CreateEntity();
    m_entity_manager.AddComponent<Position>(entity, Position{10, 10});
    m_entity_manager.AddComponent<Movement>(entity, Movement{20, 30});

    MovementSystem *movement_system = GetSystem<MovementSystem>();
    movement_system->AddEntity(entity);

    entity = m_entity_manager.CreateEntity();
    m_entity_manager.AddComponent<Animation>(entity, Animation{100, 200});

    CustomSystem *custom_system = GetSystem<CustomSystem>();
    custom_system->AddEntity(entity);
  }

  EntityManager m_entity_manager;
  Map<std::type_index, ISystem *> *m_systems = NULL;
};

struct A {
  int a = 10;
};

struct B {
  A a;
};

void Test() {
  Engine engine;

  MovementSystem movement_system;
  CustomSystem custom_system;
  engine.AddSystem<MovementSystem>(&movement_system);
  engine.AddSystem<CustomSystem>(&custom_system);

  engine.Script();
  engine.Run(0.5f);
}

// EntityManager entity_manager;

// struct ISystem {
//   virtual void Update(float dt) = 0;
// };

// struct MovementSystem : public ISystem {
//   void Update(float dt) override {
    
//   }
// };
}