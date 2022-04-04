struct RendererSystem {
  bool Initialize(GLFWManager *glfw_manager);
  void RenderBoxBegin(Position *position, Camera *camera, Program *program);
  void RenderBoxEnd(Program *program);

  GLFWManager *m_glfw_manager;
};