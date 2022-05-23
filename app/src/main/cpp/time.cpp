// TODO: Separate for different platforms later

int GetMilliseconds() {
#ifdef _WIN32
  static int base = timeGetTime();

  return timeGetTime() - base;
#elif defined __ANDROID__
  static unsigned long base = 0;
  struct timeval tp;

  gettimeofday(&tp, NULL);

  if (!base) {
    base = tp.tv_sec;
    return tp.tv_usec / 1000;
  }

  return (tp.tv_sec - base) * 1000 + tp.tv_usec / 1000;
#endif
}