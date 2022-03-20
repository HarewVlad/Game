bool VertexBuffer::Initialize(const void *data, unsigned int size) {
  glCall(glGenBuffers(1, &m_id));
  glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
  glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

  return true;
}

bool VertexBuffer::Initialize(float x, float y) {
  float vertices[] = {-x, -y, 0.0f, 0.0f,
                         -x, y,  0.0f, 1.0f,
                         x,  y,  1.0f, 1.0f,
                         x,  -y, 1.0f, 0.0f};
  glCall(glGenBuffers(1, &m_id));
  glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
  glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW));

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