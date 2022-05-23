struct WindowManager { // TODO: Rename to platform manager, replace "Window" prefix with just "ShouldClose", etc
  virtual bool WindowShouldClose() = 0; // NOTE(Vlad): Potentially slow function call due to virtual
  virtual bool IsWindowFocused() = 0; // NOTE(Vlad): Potentially slow function call due to virtual
  virtual void SwapBuffers() = 0; // NOTE(Vlad): Potentially slow function call due to virtual
  virtual void PollEvents() = 0; // NOTE(Vlad): Potentially slow function call due to virtual

  void *m_window;
  glm::vec2 m_size;
  glm::mat4 m_projection;
};