struct Background {
  bool Initialize(Box *box, Texture *texture);
  void Render();

  Texture *m_texture;
  Box *m_box;
};