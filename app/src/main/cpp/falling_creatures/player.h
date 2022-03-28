struct Player {
  bool Initialize(GLFWManager *glfw_manager, Program *program, Camera *camera, Box *box,
                  Animation *animation);
  void Render();

  Box *m_box;
  Animation *m_animation;
  Camera *m_camera;
  GLFWManager *m_glfw_manager;
  Program *m_program;
};