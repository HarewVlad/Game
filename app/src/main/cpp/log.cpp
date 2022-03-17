static void LOG(LogPriority log_priority, const char *tag, const char *fmt, ...) {
  #ifdef __ANDROID__
    __android_log_print(log_priority, tag, fmt, ...);
  #elif defined _WIN32
    // TODO: ...
  #endif
}