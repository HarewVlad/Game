struct Animation {
  void Initialize();
  void Add(int id, Texture *textures);
  void Update(State *state, float dt);
  void Update(float dt);
  Texture *GetCurrentTexture();

  TextureMap *m_textures;
  int m_id;
  int m_index;
  float m_time;
};

struct AnimationMap {
  int key;
  Animation *value;
};
