// TODO: Refactor this!!!

struct IRenderer {
  virtual void Render(EntityManager *entity_manager) = 0;
  void AddEntity(Entity entity);

  Entity *m_entities = NULL;
};