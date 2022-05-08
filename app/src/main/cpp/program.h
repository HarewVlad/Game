struct Program {
  void Initialize();
  void AddShader(const Shader *shader);
  void Link();
  void Bind();
  void Unbind();
  int GetUniformLocation(const char *name);
  void SetUniform4f(const char *name, float f1, float f2, float f3, float f4);
  void SetUniformMat4(const char *name, const glm::mat4 &mat4);
  void SetUniform1i(const char *name, int i);
  void SetUniform1f(const char *name, float i);
  float GetUniform1f(const char *name);

  unsigned int m_id;
};