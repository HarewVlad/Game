struct InputMap {
  int key;
  bool value;
};

struct Input {
  bool Initialize(GLFWManager *glfw_manager);
  void Add(int *keys, int size);
  bool IsKeyPressed(int key);
  void Update();

  InputMap *m_key_state;
  GLFWManager *m_glfw_manager;
};