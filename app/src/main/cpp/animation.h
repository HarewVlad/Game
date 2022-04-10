struct Animation {
  bool Initialize();
  void Add(int id, Texture *textures);
  void Update(float dt);
  Texture *GetCurrentTexture();
  void SetId(int id);

  TextureMap *m_textures;
  int m_id;
  int m_index;
  float m_time;
};

struct AnimationMap {
  int key;
  Animation *value;
};
