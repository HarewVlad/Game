enum class EntityId { PLAYER };

struct EntityManager {
  bool Initialize();
  void AddControl(Control *control);
  void AddAnimation(Animation *animation);
  void Update(float dt);
  void Render();

  Control **m_controls;
  Animation **m_animations;
};