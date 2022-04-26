void VertexBuffer::Initialize(const void *data, unsigned int size) {
  glCall(glGenBuffers(1, &m_id));
  BindData(data, size);
}

void VertexBuffer::Initialize(float width, float height) {
  float vertices[] = {0, 0, 0.0f, 0.0f,
                         0, height,  0.0f, 1.0f,
                         width,  height,  1.0f, 1.0f,
                         width,  0, 1.0f, 0.0f};
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