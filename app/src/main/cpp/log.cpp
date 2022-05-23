static void LOG(LogPriority log_priority, const char *tag, const char *fmt,
                ...) {
#ifdef __ANDROID__
  va_list args;
  va_start(args, fmt);

  __android_log_vprint(log_priority, tag, fmt, args);

  va_end(args);
#elif defined _WIN32
  va_list args;
  va_start(args, fmt);

  printf(LogPriorityString[log_priority]);

  while (*fmt != '\0') {
    if (*fmt == 'd') {
      int i = va_arg(args, int);
      printf("%d\n", i);
    } else if (*fmt == 'c') {
      int c = va_arg(args, int);
      printf("%c\n", c);
    } else if (*fmt == 'f') {
      double d = va_arg(args, double);
      printf("%f\n", d);
    }
    ++fmt;
  }

  va_end(args);
#endif
}