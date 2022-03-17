struct Box {
  bool Initialize(IndexBuffer *index_buffer, VertexArray *vertex_array);
  void Bind();
  void Unbind();
  void Draw();
  
  IndexBuffer *m_index_buffer;
  VertexArray *m_vertex_array;
};