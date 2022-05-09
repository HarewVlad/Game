int GetMilliseconds() {
  static int base = timeGetTime();

  return timeGetTime() - base;
}