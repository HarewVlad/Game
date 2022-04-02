struct Renderer {
  bool Initialize(GLFWManager *glfw_manager);
  void RenderBoxBegin(Position *position, Camera *camera, Program *program);
  void RenderBoxEnd(Program *program);

  GLFWManager *m_glfw_manager;
};

struct RendererMap {
  int key;
  Renderer *value; // NOTE(Vlad): Not sure that need it, only have 1 renderer
};