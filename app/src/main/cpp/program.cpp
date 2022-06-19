void Program::Initialize() {
  m_id = glCall(glCreateProgram());
}

void Program::AddShader(const Shader *shader) { glCall(glAttachShader(m_id, shader->m_id)); }

void Program::Link() {
  glCall(glLinkProgram(m_id));
  glCall(glValidateProgram(m_id));
}

void Program::Bind() { glCall(glUseProgram(m_id)); }

void Program::Unbind() { glCall(glUseProgram(0)); }

int Program::GetUniformLocation(const char *name) {
  glCall(int location = glGetUniformLocation(m_id, name));
  return location;
}

void Program::SetUniform4f(const char *name, float f1, float f2, float f3, float f4) {
  int location = GetUniformLocation(name);
  assert(location >= 0);
  glCall(glUniform4f(location, f1, f2, f3, f4));
}

void Program::SetUniformMat4(const char *name, const glm::mat4 &mat4) {
  int location = GetUniformLocation(name);
  assert(location >= 0);
  glCall(glUniformMatrix4fv(location, 1, GL_FALSE, &mat4[0][0]));
}

void Program::SetUniform1i(const char *name, int i) {
  int location = GetUniformLocation(name);
  assert(location >= 0);
  glCall(glUniform1i(location, i));
}

void Program::SetUniform1f(const char *name, float i) {
  int location = GetUniformLocation(name);
  assert(location >= 0);
  glCall(glUniform1f(location, i));
}

float Program::GetUniform1f(const char *name) {
  int location = GetUniformLocation(name);
  assert(location >= 0);
  float value;
  glCall(glGetUniformfv(m_id, location, &value));
  return value;
}

void Program::SetUniform2f(const char *name, const glm::vec2 &vec2) {
  int location = GetUniformLocation(name);
  assert(location >= 0);
  glCall(glUniform2f(location, vec2.x, vec2.y));
}