enum class EntityId { PLAYER };

// TODO: Place in different file

struct EntityInput {
  Box *m_box;
  Input *m_input;

  inline bool Initialize(Box *box, Input *input) {
    m_box = box;
    m_input = input;

    return true;
  }

  inline void Update(float dt) {
    if (m_input->GetKeyState('A')) {
      m_box->m_position.x -= 1;
    } else if (m_input->GetKeyState('D')) {
      m_box->m_position.x += 1;
    }
  }
};

struct EntityInputMap {
  int key;
  EntityInput value;
};

struct EntityAnimation {
  Animation *m_animation;

  inline bool Initialize(Animation *animation) {
    m_animation = animation;

    return true;
  }

  inline void Update(float dt) {
    m_animation->Update(dt);
  }
};

struct EntityAnimationMap {
  int key;
  EntityAnimation value;
};

struct EntityManager {
  bool Initialize();
  void AddInput(int id, Box *box, Input *input);
  void AddAnimation(int id, Animation *animation);
  void Update(float dt);

  EntityInputMap *m_input_entities;
  EntityAnimationMap *m_animation_entities;
};