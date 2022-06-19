void PlatformManagerWin32::FrameBufferSizeCallback(GLFWwindow *window, int width, int height) {
  PlatformManagerWin32 *platform_manager_win32 = (PlatformManagerWin32 *)glfwGetWindowUserPointer(window);

  platform_manager_win32->m_size = {width, height};
  platform_manager_win32->m_projection =
      glm::ortho(0.0f, static_cast<float>(width), 0.0f,
                 static_cast<float>(height), -1000.0f, 1000.0f);
}

void PlatformManagerWin32::Initialize(const glm::vec2& size, const char *title) {
  if (!glfwInit()) {
    LOG(LOG_ERROR, "WindowManagerWin32", "%s", "Unable to initialize GLFW");
    assert(0);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  m_window = glfwCreateWindow(size.x, size.y, title, NULL, NULL);
  if (!m_window) {
    glfwTerminate();
    LOG(LOG_ERROR, "WindowManagerWin32", "%s", "Unable to create GLFWwindow");
    assert(0);
  }

  glfwMakeContextCurrent((GLFWwindow *)m_window);
  glfwSetWindowUserPointer((GLFWwindow *)m_window, this);
  glfwSetFramebufferSizeCallback((GLFWwindow *)m_window, FrameBufferSizeCallback);
  glfwSwapInterval(0);

  GLenum error = glewInit();
  if (error != GLEW_OK) {
    LOG(LOG_ERROR, "WindowManagerWin32", "%s", "Unable to initialize GLEW");
    assert(0);
  }

  m_size = size;
  m_projection =
      glm::ortho(0.0f, static_cast<float>(size.x), 0.0f,
                 static_cast<float>(size.y), -1000.0f, 1000.0f);
}

int PlatformManagerWin32::GetWindowFlag(int flag) {
  return glfwGetWindowAttrib((GLFWwindow *)m_window, flag);
}

bool PlatformManagerWin32::IsFocused() {
  return GetWindowFlag(GLFW_FOCUSED) && GetWindowFlag(GLFW_HOVERED);
}

bool PlatformManagerWin32::ShouldClose() {
  return glfwWindowShouldClose((GLFWwindow *)m_window);
}

void PlatformManagerWin32::SwapBuffers() {
  glfwSwapBuffers((GLFWwindow *)m_window);
}

void PlatformManagerWin32::PollEvents() {
  glfwPollEvents();
}