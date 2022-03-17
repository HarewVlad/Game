bool Program::Initialize() {
  m_id = glCall(glCreateProgram());

  return true;
}

void Program::AddShader(const Shader *shader) { glCall(glAttachShader(m_id, shader->m_id)); }

void Program::Link() {
  glCall(glLinkProgram(m_id));
  glCall(glValidateProgram(m_id));
}

void Program::Bind() { glCall(glUseProgram(m_id)); }

void Program::Unbind() { glCall(glUseProgram(0)); }

Program::Program() { m_id = -1; }

int Program::GetUniformLocation(const char *name) {
  glCall(int location = glGetUniformLocation(m_id, name));
  return location;
}

void Program::SetUniform4f(const char *name, float f1, float f2, float f3, float f4) {
  int location = GetUniformLocation(name);
  glCall(glUniform4f(location, f1, f2, f3, f4));
}

void Program::SetUniformMat4(const char *name, const glm::mat4 &mat4) {
  int location = GetUniformLocation(name);
  glCall(glUniformMatrix4fv(location, 1, GL_FALSE, &mat4[0][0]));
}

void Program::SetUniform1i(const char *name, int i) {
  int location = GetUniformLocation(name);
  glCall(glUniform1i(location, i));
}