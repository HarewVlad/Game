GLFWManager *GLFWManager::m_glfw_manager = nullptr;

GLFWManager::GLFWManager() {
  m_glfw_manager = this;
}

void FrameBufferSizeCallbackStatic(GLFWwindow *window, int width, int height) {
  GLFWManager::m_glfw_manager->FrameBufferSizeCallback(window, width, height);
}

void GLFWManager::FrameBufferSizeCallback(GLFWwindow *window, int width, int height) {
  *m_projection =
      glm::ortho(0.0f, static_cast<float>(width), 0.0f,
                 static_cast<float>(height), -1000.0f, 1000.0f);

  m_window_size->m_width = width;
  m_window_size->m_height = height;
}

void KeyCallbackStatic(GLFWwindow *window, int key, int scancode, int action, int mods) {
  GLFWManager::m_glfw_manager->KeyCallback(window, key, scancode, action, mods);
}

void GLFWManager::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  switch (action) {
    case GLFW_PRESS:
      hmput(m_key_state, key, true);
      break;
    case GLFW_RELEASE:
      hmput(m_key_state, key, false);
      break;
    default:
      break;
  }
}

// TODO: Remove returns and place asserts
void GLFWManager::Initialize(Size *window_size, glm::mat4 *projection, const char *title) {
  if (!glfwInit()) {
    LOG(LOG_ERROR, "GLFWManager", "%s", "Unable to initialize GLFW");
    assert(0);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(window_size->m_width, window_size->m_height, title, NULL, NULL);
  if (!m_window) {
    glfwTerminate();
    LOG(LOG_ERROR, "GLFWManager", "%s", "Unable to create GLFWwindow");
    assert(0);
  }

  glfwMakeContextCurrent(m_window);
  glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallbackStatic);
  glfwSetKeyCallback(m_window, KeyCallbackStatic);
  glfwSwapInterval(0);

  GLenum error = glewInit();
  if (error != GLEW_OK) {
    LOG(LOG_ERROR, "GLFWManager", "%s", "Unable to initialize GLEW");
    assert(0);
  }

  m_window_size = window_size;
  m_projection = projection;
  m_key_state = NULL;
}

void GLFWManager::Shutdown() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

bool GLFWManager::IsKeyPressed(int key) {
  return hmget(m_key_state, key);
}

int GLFWManager::GetWindowFlag(int flag) {
  return glfwGetWindowAttrib(m_window, flag);
}

bool GLFWManager::IsWindowFocused() {
  return GetWindowFlag(GLFW_FOCUSED) && GetWindowFlag(GLFW_HOVERED);
}