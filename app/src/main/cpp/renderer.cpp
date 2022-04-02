bool Renderer::Initialize(GLFWManager *glfw_manager) {
  m_glfw_manager = glfw_manager;

  return true;
}

void Renderer::RenderBoxBegin(Position *position, Camera *camera, Program *program) { // NOTE(Vlad): Box only for know, replace with Position component or something
  program->Bind();
  program->SetUniformMat4("u_MVP", m_glfw_manager->m_projection * camera->m_view * position->GetModel());
}

void Renderer::RenderBoxEnd(Program *program) {
  program->Unbind();
}