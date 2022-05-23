void InputManagerWin32::Initialize(GLFWwindow *window) {
  m_window = window;
}

bool InputManagerWin32::IsKeyPressed(int key) {
  return glfwGetKey(m_window, key) == GLFW_PRESS;
}