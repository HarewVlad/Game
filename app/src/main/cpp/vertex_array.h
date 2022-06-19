struct VertexArray {
  void Initialize();
  void AddBuffer(Buffer *vertex_buffer,
                 const VertexBufferLayout *vertex_buffer_layout);
  void Bind();
  void Unbind();
  void Shutdown();

  unsigned int m_id;
};