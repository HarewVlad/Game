void Time::Initialize() {
  m_base = timeGetTime();
}

// NOTE(Vlad): From Quake 2
int Time::GetMilliseconds() {
  return timeGetTime() - m_base;
}

int GetMillisecondsStatic() {
  static int base = timeGetTime();

  return timeGetTime() - base;
}

void StartCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceFrequency(&li);

    PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}
