enum class ImageType {
  TEXTURE,
  ANIMATION
};

struct RendererSystem {
  void Initialize(WindowManager *window_manager);
  void RenderBoxBegin(Program *program, const glm::mat4 &mv);
  void RenderBoxEnd(Program *program);

  WindowManager *m_window_manager;
};

struct RendererData {
  ImageType type;
};