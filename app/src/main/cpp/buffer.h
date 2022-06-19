struct Buffer {
  void Initialize(GLenum type, GLenum usage, const void *data, unsigned int size, int count);
  void Bind();
  void Unbind();
  void Shutdown();
  void BindData(const void *data, unsigned int size);

  unsigned int m_id;
  GLenum m_type;
  GLenum m_usage;
  int m_count; // NOTE(Vlad): Count of elements
};