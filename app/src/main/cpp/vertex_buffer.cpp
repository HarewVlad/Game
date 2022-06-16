void VertexBuffer::Initialize(const void *data, unsigned int size) {
  glCall(glGenBuffers(1, &m_id));
  BindData(data, size);
}

void VertexBuffer::Initialize(const glm::vec2& size) {
  float vertices[] = {0, 0, 0.0f, 0.0f,
                         0, size.y,  0.0f, 1.0f,
                         size.x,  size.y,  1.0f, 1.0f,
                         size.x,  0, 1.0f, 0.0f};
  glCall(glGenBuffers(1, &m_id));
  BindData(&vertices, sizeof(vertices));
}

void VertexBuffer::Bind() { glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id)); }
void VertexBuffer::Unbind() { glCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); }
void VertexBuffer::Shutdown() { glCall(glDeleteBuffers(1, &m_id)); }
void VertexBuffer::BindData(const void *data, unsigned int size) {
  glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
  glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
  glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}