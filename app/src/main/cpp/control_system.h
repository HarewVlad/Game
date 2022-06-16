struct ControlSystem : public ISystem {
  void Initialize(InputManager *input_manager);
  void Update(EntityManager *entity_manager, float dt) override;

  InputManager *m_input_manager;
};