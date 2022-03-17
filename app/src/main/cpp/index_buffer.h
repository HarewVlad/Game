struct IndexBuffer {
  IndexBuffer();
  bool Initialize(const unsigned int *data, unsigned int count);
  void Bind();
  void Unbind();
  
  unsigned int m_id;
  unsigned int m_count;
};