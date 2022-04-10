struct Control {
  bool Initialize(GLFWManager *glfw_manager); // TODO: Need to actually create InputManager ... because for android it is different
  void Update(Movement *movement, Animation *animation, float dt);

  GLFWManager *m_glfw_manager;
};

struct ControlMap {
  int key;
  Control *value;
};
