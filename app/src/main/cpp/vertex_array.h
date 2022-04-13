struct VertexArray {
  void Initialize();
  void AddBuffer(VertexBuffer *vertex_buffer,
                 VertexBufferLayout *vertex_buffer_layout);
  void Bind();
  void Unbind();
  void Shutdown();

  unsigned int m_id;
};