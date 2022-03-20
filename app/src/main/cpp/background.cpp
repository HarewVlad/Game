bool Background::Initialize(GLFWManager *glfw_manager, Program *program, Camera *camera, Box *box, Texture *texture) {
  m_glfw_manager = glfw_manager;
  m_program = program;
  m_texture = texture;
  m_camera = camera;
  m_box = box;

  return true;
}

void Background::Render() {
  m_program->Bind();

  m_program->SetUniformMat4("u_MVP", m_glfw_manager->m_projection * m_camera->m_view * m_box->GetModel());
  m_program->SetUniform1i("u_Texture", 0);

  m_box->Bind();
  m_texture->Bind();
  m_box->Draw();
  m_texture->Unbind();
  m_box->Unbind();

  m_program->Unbind();
}