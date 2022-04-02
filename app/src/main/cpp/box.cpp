bool Box::Initialize(IndexBuffer *index_buffer, VertexArray *vertex_array) {
  m_vertex_array = vertex_array;
  m_index_buffer = index_buffer;
  
  return true;
}

void Box::Bind() {
  m_vertex_array->Bind();
  m_index_buffer->Bind();
}

void Box::Unbind() {
  m_vertex_array->Unbind();
  m_index_buffer->Unbind();
}

void Box::Draw() {
  glDrawElements(GL_TRIANGLES, m_index_buffer->m_count, GL_UNSIGNED_INT, nullptr);
}