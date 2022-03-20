struct FallingCreatures : public Game {
  bool Initialize(Background *background);
  void Shutdown() override;
  void Render() override;
  void Update(float dt) override;

  Background *m_background;
};