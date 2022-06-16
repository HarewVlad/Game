// TODO: Completele remove it, leave only VertexBuffer, VertexBufferLayout, IndexBuffer, VertexArray as a separate components
void Box::Initialize(const glm::vec2& size) {
  m_index_buffer.Initialize();

  m_vertex_buffer_layout.Push(GL_FLOAT, 2);
  m_vertex_buffer_layout.Push(GL_FLOAT, 2);

  m_vertex_buffer.Initialize(size);

  m_vertex_array.Initialize();
  m_vertex_array.AddBuffer(&m_vertex_buffer, &m_vertex_buffer_layout);
}

void Box::Bind() {
  m_vertex_array.Bind();
  m_index_buffer.Bind();
}

void Box::Unbind() {
  m_vertex_array.Unbind();
  m_index_buffer.Unbind();
}

void Box::Draw() {
  glDrawElements(GL_TRIANGLES, m_index_buffer.m_count, GL_UNSIGNED_INT, nullptr);
}