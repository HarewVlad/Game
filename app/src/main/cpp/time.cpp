int GetMilliseconds() {
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
