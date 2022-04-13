void VertexArray::Initialize() {
  glCall(glGenVertexArrays(1, &m_id));
}

void VertexArray::AddBuffer(VertexBuffer *vertex_buffer,
               VertexBufferLayout *vertex_buffer_layout) {
  glCall(glBindVertexArray(m_id));
  vertex_buffer->Bind();

  const auto &elements = vertex_buffer_layout->m_elements;
  unsigned int offset = 0;
  for (unsigned int i = 0; i < arrlen(elements); ++i) {
    const auto &element = elements[i];

    glCall(glEnableVertexAttribArray(i));
    glCall(glVertexAttribPointer(i, element.m_count, element.m_type, element.m_normalized,
                          vertex_buffer_layout->m_stride, (const void *)offset));
    offset += element.m_count * Utility::OpenGL::GetTypeSize(element.m_type);
  }
}
void VertexArray::Bind() { glCall(glBindVertexArray(m_id)); }
void VertexArray::Unbind() { glCall(glBindVertexArray(0)); }
void VertexArray::Shutdown() { glCall(glDeleteVertexArrays(1, &m_id)); }