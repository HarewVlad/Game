struct Box {
  void Initialize(IndexBuffer *index_buffer, VertexArray *vertex_array);
  void Bind();
  void Unbind();
  void Update(float dt);
  void Draw();
  void Shutdown();

  IndexBuffer *m_index_buffer;
  VertexArray *m_vertex_array;
};

struct BoxMap {
  int key;
  Box *value;
};