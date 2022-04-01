struct Renderer {
  bool Initialize(GLFWManager *glfw_manager);
  void RenderBoxBegin(Box *box, Camera *camera, Program *program);
  void RenderBoxEnd(Program *program);

  GLFWManager *m_glfw_manager;
};