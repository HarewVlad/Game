bool Player::Initialize(GLFWManager *glfw_manager,
                        Program *program, Camera *camera, Box *box, Animation *animation) {

  m_box = box;
  m_animation = animation;
  m_camera = camera;
  m_glfw_manager = glfw_manager;
  m_program = program;

  return true;
}

// TODO: Is it right to put this code here?
void Player::Render() {
  m_program->Bind();

  m_program->SetUniformMat4("u_MVP", m_glfw_manager->m_projection * m_camera->m_view * m_box->GetModel());
  m_program->SetUniform1i("u_Texture", 0);

  Texture *texture = m_animation->GetCurrentTexture();

  m_box->Bind();
  texture->Bind();
  m_box->Draw();
  texture->Bind();
  m_box->Unbind();

  m_program->Unbind();
}
//