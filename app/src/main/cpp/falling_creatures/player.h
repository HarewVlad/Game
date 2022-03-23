struct Player {
  bool Initialize(GLFWManager *glfw_manager, Program *program, Camera *camera, Input *input, Box *box,
                  Animation *animation);
  void Render();
  void Update(float dt);

  Box *m_box;
  Animation *m_animation;
  Input *m_input;
  Camera *m_camera;
  GLFWManager *m_glfw_manager;
  Program *m_program;
};