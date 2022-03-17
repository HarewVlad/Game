bool Game::Initialize(Program *program, Background *background) {
  m_background = background;
  m_program = program;

  return true;
}

// NOTE: Test
void Game::Render() {
  m_program->Bind();
   glCall(glEnable(GL_BLEND));
  glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(1080), 0.0f, static_cast<float>(1920), -1000.0f, 1000.0f);
  glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  glm::mat4 model = glm::mat4(1.0f);
  m_program->SetUniformMat4(
      "u_MVP", proj * view * model);
  m_program->SetUniform1i("u_Texture", 0);
  m_background->Render();
  m_program->Unbind();
}

void Game::Update(float dt) {
  
}