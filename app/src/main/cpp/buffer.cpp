void Buffer::Initialize(GLenum type, GLenum usage, const void *data, unsigned int size, int count) {
  m_type = type;
  m_usage = usage;
  m_count = count;

  glCall(glGenBuffers(1, &m_id));
  BindData(data, size);
}

void Buffer::Bind() { glCall(glBindBuffer(m_type, m_id)); }
void Buffer::Unbind() { glCall(glBindBuffer(m_type, 0)); }
void Buffer::Shutdown() { glCall(glDeleteBuffers(1, &m_id)); }
void Buffer::BindData(const void *data, unsigned int size) {
  glCall(glBindBuffer(m_type, m_id));
  glCall(glBufferData(m_type, size, data, m_usage));
  glCall(glBindBuffer(m_type, 0));
}