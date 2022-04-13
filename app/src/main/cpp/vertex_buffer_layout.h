struct VertexBufferElement {
  unsigned int m_type;
  unsigned int m_count;
  unsigned char m_normalized;
};

struct VertexBufferLayout {
  void Initialize();
  void Push(unsigned int type, unsigned int count, unsigned char normilized = GL_FALSE);

  VertexBufferElement *m_elements;
  unsigned int m_stride;
};