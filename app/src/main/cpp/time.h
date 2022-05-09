// NOTE(Vlad): Mb use glfwGetTime(); for Linux later
int GetMilliseconds();

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter();
double GetCounter();