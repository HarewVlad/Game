void RendererSystem::Initialize(WindowManager *window_manager) {
  m_window_manager = window_manager;
}

void RendererSystem::RenderBoxBegin(Program *program, const glm::mat4 &mv) {
  program->Bind();
  program->SetUniformMat4("u_MVP", m_window_manager->m_projection * mv);
}

void RendererSystem::RenderBoxEnd(Program *program) {
  program->Unbind();
}