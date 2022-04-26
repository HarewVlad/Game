enum class ImageType {
  TEXTURE,
  ANIMATION
};

struct RendererSystem {
  void Initialize(GLFWManager *glfw_manager);
  void RenderBoxBegin(Position *position, CameraSystem *camera_system, Program *program);
  void RenderBoxEnd(Program *program);

  GLFWManager *m_glfw_manager;
};

struct RendererData {
  int id;
  ImageType type;
};