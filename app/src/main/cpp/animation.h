struct Animation {
  bool Initialize();
  void Add(Texture *textures, int size);
  void Update(float dt);
  Texture *GetCurrentTexture();

  Texture *m_textures;
  int m_index;
  float m_time;
};