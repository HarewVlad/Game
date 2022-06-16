void BoxRenderer::Initialize(glm::mat4 *view, glm::mat4 *projection) {
  m_view = view;
  m_projection = projection;
}

void BoxRenderer::Render(EntityManager *entity_manager) {
  for (int i = 0; i < arrlen(m_entities); ++i) {
    Entity entity = m_entities[i];

    RenderInfo *render_info = entity_manager->GetComponent<RenderInfo>(entity);

    if (!render_info->m_draw) {
      continue;
    }

    Box *box = entity_manager->GetComponent<Box>(entity);
    Position *position = entity_manager->GetComponent<Position>(entity);
    Program *program = entity_manager->GetComponent<Program>(entity);
    Texture *texture;

    const glm::mat4 mvp = *m_projection * *m_view * position->GetModel();

    program->Bind();
    program->SetUniformMat4("u_MVP", mvp);
    program->SetUniform1i("u_Texture", 0);

    switch (render_info->m_texture_type) {
      case TextureType_Animation: {
        Animation *animation = entity_manager->GetComponent<Animation>(entity);
        
        Array<Texture> *textures = entity_manager->GetComponent<Array<Texture>>(animation->m_type);
        texture = textures->Get(animation->m_index);
      }
      break;
      case TextureType_Single: {
        texture = entity_manager->GetComponent<Texture>(entity);
      }
      break;
    }

    texture->Bind();

    box->Bind();
    box->Draw();
    box->Unbind();

    texture->Unbind();

    program->Unbind();
  }
}