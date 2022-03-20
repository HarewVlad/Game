bool Box::Initialize(IndexBuffer *index_buffer, VertexArray *vertex_array, float x, float y) {
  m_vertex_array = vertex_array;
  m_index_buffer = index_buffer;
  m_position = {x, y};
  m_model = glm::mat4(1.0f);
  
  return true;
}

const glm::mat4 Box::GetModel() {
  return glm::translate(m_model, glm::vec3(m_position, 0));
  // TODO: Also restore rotations when they added
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