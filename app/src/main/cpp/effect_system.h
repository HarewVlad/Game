enum EffectType {
  EffectType_None = 0,
  EffectType_Blink = 1 << 0
};

struct EffectSystem : public ISystem {
  void Update(EntityManager *entity_manager, float dt) override;
  void AddEntity(Entity entity, int type);

  int *m_effect_types = NULL;
};