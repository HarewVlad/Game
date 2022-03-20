bool Input::Initialize(GLFWManager *glfw_manager) {
  m_key_state = NULL;
  m_glfw_manager = glfw_manager;

  return true;
}

void Input::Add(int *keys, int size) {
  for (int i = 0; i < size; ++i) {
    hmput(m_key_state, keys[i], 0);
  }
}

bool Input::IsKeyPressed(int key) {
  int state = glfwGetKey(m_glfw_manager->m_window, key);
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

void Input::Update() {
  for (int i = 0; i < hmlen(m_key_state); ++i) {
    if (IsKeyPressed(m_key_state[i].key)) {
      m_key_state[i].value = 1;
    } else {
      m_key_state[i].value = 0;
    }
  }
}