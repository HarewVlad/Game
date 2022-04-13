void IndexBuffer::Initialize(const unsigned int *data, unsigned int count) {
  glCall(glGenBuffers(1, &m_id));
  glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
  glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

  m_count = count;
}

void IndexBuffer::Initialize() {
  unsigned int indices[] = {0, 1, 2, 0, 2, 3};
  m_count = 6;

  glCall(glGenBuffers(1, &m_id));
  glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
  glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW));
}

void IndexBuffer::Bind() {
  glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void IndexBuffer::Unbind() {
  glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}