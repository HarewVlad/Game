bool Control::Initialize(GLFWManager *glfw_manager, float speed) {
  m_glfw_manager = glfw_manager;
  m_speed = speed;

  return true;
}

// TODO: Make callback to define custom controls for something later ...
void Control::Update(Movement *movement, Animation *animation, float dt) {
  // TODO: Mb apply forces instead of directly changing velocity
  if (m_glfw_manager->IsKeyPressed(GLFW_KEY_A)) {
    movement->m_velocity.x -= m_speed;
    animation->SetId(1);
  } else if (m_glfw_manager->IsKeyPressed(GLFW_KEY_D)) {
    movement->m_velocity.x += m_speed;
    animation->SetId(1);
  } else if (m_glfw_manager->IsKeyPressed(GLFW_KEY_W)) {
    movement->m_velocity.y += m_speed;
    animation->SetId(1);
  } else if (m_glfw_manager->IsKeyPressed(GLFW_KEY_S)) {
    movement->m_velocity.y -= m_speed;
    animation->SetId(1);
  } else {
    animation->SetId(0);
  }
}