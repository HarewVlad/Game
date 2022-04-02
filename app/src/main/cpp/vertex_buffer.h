struct VertexBuffer {
  bool Initialize(const void *data, unsigned int size);
  bool Initialize(float width, float height);
  void Bind();
  void Unbind();
  void Free();
  void BindData(const void *data, unsigned int size);

  unsigned int m_id;
};