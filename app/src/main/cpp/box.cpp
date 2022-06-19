// TODO: Completele remove it, leave only VertexBuffer, VertexBufferLayout, IndexBuffer, VertexArray as a separate components
void Box::Initialize(const glm::vec2& size) {
  unsigned int indices[] = {0, 1, 2, 0, 2, 3};

  float vertices[] = {0, 0, 0.0f, 0.0f,
                      0, size.y,  0.0f, 1.0f,
                      size.x,  size.y,  1.0f, 1.0f,
                      size.x,  0, 1.0f, 0.0f};

  m_index_buffer.Initialize(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, &indices[0], sizeof(indices), sizeof(indices) / sizeof(unsigned int));
  m_vertex_buffer.Initialize(GL_ARRAY_BUFFER, GL_STATIC_DRAW, &vertices[0], sizeof(vertices), sizeof(vertices) / sizeof(float));

  m_vertex_buffer_layout.Push(GL_FLOAT, 2);
  m_vertex_buffer_layout.Push(GL_FLOAT, 2);

  m_vertex_array.Initialize();
  m_vertex_array.AddBuffer(&m_vertex_buffer, &m_vertex_buffer_layout);
}

void Box::Bind() {
  m_vertex_array.Bind();
  m_index_buffer.Bind();
}

void Box::Unbind() {
  m_vertex_array.Unbind();
  m_index_buffer.Unbind();
}

void Box::Draw() {
  glDrawElements(GL_TRIANGLES, m_index_buffer.m_count, GL_UNSIGNED_INT, nullptr);
}