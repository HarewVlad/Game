// NOTE(Vlad): Mb use glfwGetTime(); for Linux later

struct Time {
  void Initialize();
  int GetMilliseconds();

  int m_base;
};