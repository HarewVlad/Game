// TODO: Shutdown method when need to delete this component (And for any other components)

struct Spritesheet {
  void Initialize(const glm::vec2 &size);
  void Add(int id, int count);
  const glm::vec2 Offset(int id, int index);

  glm::vec2 m_size;
  Map<int, int> *m_textures = NULL;
};