struct PlatformManager {
  virtual bool ShouldClose() = 0;
  virtual bool IsFocused() = 0;
  virtual void SwapBuffers() = 0;
  virtual void PollEvents() = 0;

  void *m_window;
  glm::vec2 m_size;
  glm::mat4 m_projection;
};