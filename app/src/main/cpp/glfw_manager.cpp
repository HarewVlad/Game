bool GLFWManager::Initialize(UINT width, UINT height, const char *title) {
  if (!glfwInit()) {
    LOG(LOG_ERROR, "GLFWManager", "%s", "Unable to initialize GLFW");
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!m_window) {
    glfwTerminate();
    LOG(LOG_ERROR, "GLFWManager", "%s", "Unable to create GLFWwindow");
    return false;
  }

  glfwMakeContextCurrent(m_window);
  glfwSwapInterval(1);

  GLenum error = glewInit();
  if (error != GLEW_OK) {
    LOG(LOG_ERROR, "GLFWManager", "%s", "Unable to initialize GLEW");
    return false;
  }

  m_width = width;
  m_height = height;

  return true;
}

void GLFWManager::Shutdown() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}