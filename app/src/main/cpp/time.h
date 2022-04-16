// NOTE(Vlad): Mb use glfwGetTime(); for Linux later

struct Time {
  void Initialize();
  int GetMilliseconds();

  int m_base;
};

int GetMillisecondsStatic();

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter();
double GetCounter();