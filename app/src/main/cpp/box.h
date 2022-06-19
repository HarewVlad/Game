struct Box {
  void Initialize(const glm::vec2& size);
  void Bind();
  void Unbind();
  void Draw();

  Buffer m_index_buffer;
  Buffer m_vertex_buffer;
  VertexBufferLayout m_vertex_buffer_layout;
  VertexArray m_vertex_array;
};