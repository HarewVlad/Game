enum TextureType {
  TextureType_None,
  TextureType_Single,
  TextureType_Animation
};

struct RenderInfo {
  int m_texture_type;
  bool m_draw;
};

struct BoxRenderer : public IRenderer {
  void Initialize(glm::mat4 *view, glm::mat4 *projection);
  void Render(EntityManager *entity_manager) override;

  glm::mat4 *m_view;
  glm::mat4 *m_projection;
};