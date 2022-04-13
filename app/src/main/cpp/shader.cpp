// TODO: Remove returns and place asserts
bool Shader::Initialize(const char *code, unsigned int type) {
  m_id = glCall(glCreateShader(type));

  glCall(glShaderSource(m_id, 1, &code, nullptr));
  glCall(glCompileShader(m_id));

  int result;
  glCall(glGetShaderiv(m_id, GL_COMPILE_STATUS, &result));
  if (result != GL_TRUE) {
    int length;
    glCall(glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &length));
    char *message = (char *)malloc(length);
    glCall(glGetShaderInfoLog(m_id, length, &length, message));
    LOG(LOG_ERROR, "Shader", "%s", message);
    glCall(glDeleteShader(m_id));
    free(message);
    return false;
  }

  return true;
}