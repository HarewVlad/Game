struct VertexArray {
  bool Initialize();
  void AddBuffer(VertexBuffer *vertex_buffer,
                 VertexBufferLayout *vertex_buffer_layout);
  void Bind();
  void Unbind();
  void Free();

  unsigned int m_id;
};