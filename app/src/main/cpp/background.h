struct Background {
  bool Initialize(GLFWManager *glfw_manager, Program *program, Camera *camera, Box *box, Texture *texture);
  void Render();

  GLFWManager *m_glfw_manager;
  Program *m_program;
  Texture *m_texture;
  Camera *m_camera; // NOTE(Vlad): Need to follow the camera
  Box *m_box;
};