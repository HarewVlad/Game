VertexBuffer::VertexBuffer() { m_id = 0; }

bool VertexBuffer::Initialize(const void *data, unsigned int size) {
  glCall(glGenBuffers(1, &m_id));
  glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
  glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

  return true;
}

void VertexBuffer::Bind() { glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id)); }
void VertexBuffer::Unbind() { glCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); }
void VertexBuffer::Free() { glCall(glDeleteBuffers(1, &m_id)); }
void VertexBuffer::BindData(const void *data, unsigned int size) {
  glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
  glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
  glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}