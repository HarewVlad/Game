// TODO: Need to shutdown resources

bool FallingCreatures::Initialize(Background *background) {
  m_background = background;

  return true;
}

// NOTE: Test
void FallingCreatures::Render() {
  m_background->Render();
}

void FallingCreatures::Update(float dt) {}

void FallingCreatures::Shutdown() {}