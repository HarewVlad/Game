IndexBuffer::IndexBuffer() {
  m_id = 0;
  m_count = 0;
}

bool IndexBuffer::Initialize(const unsigned int *data, unsigned int count) {
  glCall(glGenBuffers(1, &m_id));
  glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
  glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

  m_count = count;

  return true;
}

void IndexBuffer::Bind() {
  glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void IndexBuffer::Unbind() {
  glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}