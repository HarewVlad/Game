bool RendererSystem::Initialize(GLFWManager *glfw_manager) {
  m_glfw_manager = glfw_manager;

  return true;
}

void RendererSystem::RenderBoxBegin(Position *position, CameraSystem *camera_system, Program *program) {
  program->Bind();
  program->SetUniformMat4("u_MVP", m_glfw_manager->m_projection * camera_system->GetView() * position->GetModel());
}

void RendererSystem::RenderBoxEnd(Program *program) {
  program->Unbind();
}