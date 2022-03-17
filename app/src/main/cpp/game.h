struct Game {
  bool Initialize(Program *program, Background *background);
  void Shutdown();
  void Render();

  Background *m_background;
  Program *m_program;
};