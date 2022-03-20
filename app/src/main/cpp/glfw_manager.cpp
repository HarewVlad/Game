GLFWManager *GLFWManager::m_glfw_manager = nullptr;

GLFWManager::GLFWManager() {
  m_glfw_manager = this;
}

void FrameBufferSizeCallbackStatic(GLFWwindow *window, int width, int height) {
  GLFWManager::m_glfw_manager->FrameBufferSizeCallback(window, width, height);
}

void GLFWManager::FrameBufferSizeCallback(GLFWwindow *window, int width, int height) {
  m_projection =
      glm::ortho(0.0f, static_cast<float>(width), 0.0f,
                 static_cast<float>(height), -1000.0f, 1000.0f);

  m_width = width;
  m_height = height;
}

bool GLFWManager::Initialize(int width, int height, const char *title) {
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
  glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallbackStatic);
  glfwSwapInterval(1);

  GLenum error = glewInit();
  if (error != GLEW_OK) {
    LOG(LOG_ERROR, "GLFWManager", "%s", "Unable to initialize GLEW");
    return false;
  }

  m_width = width;
  m_height = height;
  m_projection =
      glm::ortho(0.0f, static_cast<float>(width), 0.0f,
                 static_cast<float>(height), -1000.0f, 1000.0f);

  return true;
}

void GLFWManager::Shutdown() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}