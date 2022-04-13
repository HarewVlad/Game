struct Control {
  void Initialize(GLFWManager *glfw_manager, float speed); // TODO: Need to actually create InputManager ... because for android it is different
  void Update(Movement *movement, Animation *animation, float dt);

  std::function<void()> m_on_movement;
  GLFWManager *m_glfw_manager;
  float m_speed;
};

struct ControlMap {
  int key;
  Control *value;
};
