enum class Entity { BACKGROUND, PLAYER }; // TODO: Remove it from there

struct ControlMap {
  Entity key;
  Control *value;
};

struct AnimationMap {
  Entity key;
  Animation *value;
};

struct CameraMap {
  Entity key;
  Camera *value;
};

struct BoxMap {
  Entity key;
  Box *value;
};

struct RendererMap {
  Entity key;
  Renderer *value; // NOTE(Vlad): Not sure that need it, only have 1 renderer
};

struct ProgramMap {
  Entity key;
  Program *value;
};

struct TextureMap {
  Entity key;
  Texture *value;
};

struct EntityManager {
  bool Initialize();
  void AddControl(Entity id, Control *control);
  void AddAnimation(Entity id, Animation *animation);
  void AddCamera(Entity id, Camera *camera);
  void AddRenderer(Entity id, Renderer *renderer);
  void AddBox(Entity id, Box *box);
  void AddProgram(Entity id, Program *program);
  void AddTexture(Entity id, Texture *texture);
  void Update(float dt);
  void Render();

  ControlMap *m_controls;
  AnimationMap *m_animations;
  CameraMap *m_cameras;
  BoxMap *m_boxes;
  RendererMap *m_renderers;
  ProgramMap *m_programs;
  TextureMap *m_textures;
};