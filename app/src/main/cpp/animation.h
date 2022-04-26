// TODO: Make it AnimationSystem and take just sprites and ids

struct Animation {
  void Initialize();
  void Add(int id, Texture *textures);
  inline void Update(float dt);
  inline Texture &GetCurrentTexture();
  inline void SetAnimation(int id);

  TextureMap *m_textures;
  int m_id;
  int m_index;
  float m_time;
};

struct AnimationMap {
  int key;
  Animation *value;
};
