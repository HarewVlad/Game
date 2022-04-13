struct IndexBuffer {
  void Initialize(const unsigned int *data, unsigned int count);
  void Initialize();
  void Bind();
  void Unbind();
  
  unsigned int m_id;
  unsigned int m_count;
};