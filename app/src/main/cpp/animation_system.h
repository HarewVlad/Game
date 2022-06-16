struct AnimationSystem : public ISystem {
  void Update(EntityManager *entity_manager, float dt) override;
};