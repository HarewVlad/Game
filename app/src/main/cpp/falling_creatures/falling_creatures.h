struct FallingCreatures : public Game {
  bool Initialize(Background *background, Player *player);
  void Shutdown() override;
  void Render() override;
  void Update(float dt) override;

  Background *m_background;
  Player *m_player;
};