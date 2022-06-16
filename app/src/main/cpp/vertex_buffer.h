struct VertexBuffer {
  void Initialize(const void *data, unsigned int size);
  void Initialize(const glm::vec2& size);
  void Bind();
  void Unbind();
  void Shutdown();
  void BindData(const void *data, unsigned int size);

  unsigned int m_id;
};