struct Box {
  bool Initialize(IndexBuffer *index_buffer, VertexArray *vertex_array, float x, float y);
  void Bind();
  void Unbind();
  void Update(float dt);
  void Draw();
  const glm::mat4 GetModel();

  IndexBuffer *m_index_buffer;
  VertexArray *m_vertex_array;
  glm::vec2 m_position;
  glm::mat4 m_model; // NOTE(Vlad): Do manipulations with box (rotate, scale, ...) // TODO: Move out from there to separate entity Position or something
};