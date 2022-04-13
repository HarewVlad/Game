struct VertexBuffer {
  void Initialize(const void *data, unsigned int size);
  void Initialize(float width, float height);
  void Bind();
  void Unbind();
  void Shutdown();
  void BindData(const void *data, unsigned int size);

  unsigned int m_id;
};