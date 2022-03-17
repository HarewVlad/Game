struct VertexBufferElement {
  unsigned int m_type;
  unsigned int m_count;
  unsigned char m_normalized;
};

struct VertexBufferLayout {
  VertexBufferLayout();
  bool Initialize();

  std::vector<VertexBufferElement> m_elements;
  unsigned int m_stride;

  template <typename T>
  void Push(unsigned int count) {
    LOG(LOG_ERROR, Global_LogTag, "%s", "VertexBufferLayout::Push");
  }

  template <>
  void Push<float>(unsigned int count) {
    m_elements.push_back(VertexBufferElement{ GL_FLOAT, count, GL_FALSE });
    m_stride += Utility::OpenGL::GetTypeSize(GL_FLOAT) * count;
  }

  template <>
  void Push<unsigned int>(unsigned int count) {
    m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    m_stride += Utility::OpenGL::GetTypeSize(GL_UNSIGNED_INT) * count;
  }

  template <>
  void Push<unsigned char>(unsigned int count) {
    m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    m_stride += Utility::OpenGL::GetTypeSize(GL_UNSIGNED_BYTE) * count;
  }
};