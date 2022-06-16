struct Box {
  void Initialize(const glm::vec2& size);
  void Bind();
  void Unbind();
  void Draw();

  IndexBuffer m_index_buffer;
  VertexBufferLayout m_vertex_buffer_layout;
  VertexBuffer m_vertex_buffer;
  VertexArray m_vertex_array;
};