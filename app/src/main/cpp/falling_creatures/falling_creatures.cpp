// TODO: Need to shutdown resources

bool FallingCreatures::Initialize(Background *background, Player *player) {
  m_background = background;
  m_player = player;

  return true;
}

void FallingCreatures::Render() {
  m_background->Render();
  m_player->Render();
}

void FallingCreatures::Update(float dt) {
  m_player->Update(dt);
}

void FallingCreatures::Shutdown() {}