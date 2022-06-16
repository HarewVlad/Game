struct ISystem {
  virtual void Update(EntityManager *entity_manager, float dt) = 0;
  void AddEntity(Entity entity);

  Entity *m_entities = NULL;
};