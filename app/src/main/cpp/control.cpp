bool Control::Initialize(GLFWManager *glfw_manager) {
  m_glfw_manager = glfw_manager;

  return true;
}

// TODO: Make callback to define custom controls for something later ...
void Control::Update(Movement *movement, float dt) {
  if (m_glfw_manager->IsKeyPressed(GLFW_KEY_A)) {
    movement->m_velocity.x += 50;
  } else if (m_glfw_manager->IsKeyPressed(GLFW_KEY_D)) {
    movement->m_velocity.x -= 50;
  } else if (m_glfw_manager->IsKeyPressed(GLFW_KEY_W)) {
  } else if (m_glfw_manager->IsKeyPressed(GLFW_KEY_S)) {
  }
}