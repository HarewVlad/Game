bool Background::Initialize(Box *box, Texture *texture) {
  m_texture = texture;
  m_box = box;

  return true;
}

void Background::Render() {
  m_box->Bind();
  m_texture->Bind();
  m_box->Draw();
  m_texture->Unbind();
  m_box->Unbind();
}