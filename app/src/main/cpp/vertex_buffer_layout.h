struct VertexBufferElement {
  unsigned int m_type;
  unsigned int m_count;
  unsigned char m_normalized;
};

struct VertexBufferLayout {
  bool Initialize();
  void Push(unsigned int type, unsigned int count, unsigned int normilized = GL_FALSE);

  VertexBufferElement *m_elements = NULL;
  unsigned int m_stride;
};