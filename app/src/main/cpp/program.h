struct Program {
  Program();
  bool Initialize();
  void AddShader(const Shader *shader);
  void Link();
  void Bind();
  void Unbind();
  int GetUniformLocation(const char *name);
  void SetUniform4f(const char *name, float f1, float f2, float f3, float f4);
  void SetUniformMat4(const char *name, const glm::mat4 &mat4);
  void SetUniform1i(const char *name, int i);

  unsigned int m_id;
};