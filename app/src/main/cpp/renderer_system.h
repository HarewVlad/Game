enum class ImageType {
  TEXTURE,
  ANIMATION
};

struct RendererSystem {
  void Initialize(glm::mat4 *projection);
  void RenderBoxBegin(Program *program, const glm::mat4 &mv);
  void RenderBoxEnd(Program *program);

  glm::mat4 *m_projection;
};

struct RendererData {
  ImageType type;
};