void RendererSystem::Initialize(glm::mat4 *projection) {
  m_projection = projection;
}

void RendererSystem::RenderBoxBegin(Program *program, const glm::mat4 &mv) {
  program->Bind();
  program->SetUniformMat4("u_MVP", (*m_projection) * mv);
}

void RendererSystem::RenderBoxEnd(Program *program) {
  program->Unbind();
}