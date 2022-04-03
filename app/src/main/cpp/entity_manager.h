struct EntityManager {
  bool Initialize();
  void AddControl(int id, Control *control);
  void AddAnimation(int id, Animation *animation);
  void AddCamera(int id, Camera *camera);
  void AddRenderer(int id, Renderer *renderer);
  void AddBox(int id, Box *box);
  void AddProgram(int id, Program *program);
  void AddTexture(int id, Texture *texture);
  void AddPosition(int id, Position *position);
  void AddMovement(int id, Movement *movement);
  void AddPhysics(int id, Physics *physics);
  
  void Update(float dt);
  void Render();

  ControlMap *m_controls;
  AnimationMap *m_animations;
  CameraMap *m_cameras;
  BoxMap *m_boxes;
  RendererMap *m_renderers;
  ProgramMap *m_programs;
  TextureMap *m_textures;
  PositionMap *m_positions;
  MovementMap *m_movements;
  PhysicsMap *m_physics;
};