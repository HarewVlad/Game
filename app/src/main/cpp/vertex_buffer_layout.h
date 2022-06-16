struct VertexBufferElement {
  unsigned int m_type;
  unsigned int m_count;
  unsigned char m_normalized;
};

struct VertexBufferLayout {
  void Push(unsigned int type, unsigned int count, unsigned char normilized = GL_FALSE);

  VertexBufferElement *m_elements = NULL;
  unsigned int m_stride = 0;
};