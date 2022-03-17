// NOTE(Vlad): Cloning Falling Creatures game there

struct Game {
  bool Initialize(Program *program, Background *background);
  void Shutdown();
  void Render();
  void Update(float dt);

  Background *m_background;
  Program *m_program;
};