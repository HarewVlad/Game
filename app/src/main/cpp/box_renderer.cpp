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

    program->Bind();
    box->Bind();

    Texture *texture;
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
      case TextureType_Spritesheet: {
        Spritesheet *spritesheet = entity_manager->GetComponent<Spritesheet>(entity);

        texture = entity_manager->GetComponent<Texture>(entity);

        const glm::vec2 offset = spritesheet->Offset(PlayerAnimation_Idle, 0);

        float x = 1;

        const glm::vec2 min = {x * 1.0f / spritesheet->m_size.x, 1};
        const glm::vec2 max = {1.0f / spritesheet->m_size.x + min.x, 1 - 1.0f / spritesheet->m_size.y / 1.5f};

        // New coordinates here
        float player_vertices[] = {0, 0, min.x, max.y,
         0, 100,  min.x, min.y,
         100,  100,  max.x, min.y,
         100,  0, max.x, max.y};

         box->m_vertex_buffer.BindData(&player_vertices, sizeof(player_vertices));
      }
      break;
    }

    const glm::mat4 mvp = *m_projection * *m_view * position->GetModel();
    
    // program->Bind();

    program->SetUniformMat4("u_MVP", mvp);
    program->SetUniform1i("u_Texture", 0);

    texture->Bind();

    // box->Bind();
    box->Draw();
    box->Unbind();

    texture->Unbind();

    program->Unbind();
  }
}