namespace Utility {
  void Wait(int milliseconds) {
    #ifdef __ANDROID__
      usleep(milliseconds * 1000); // NOTE(Vlad): usleep is in microseconds
    #elif defined _WIN32
      Sleep(milliseconds);
    #endif
  }

// Unfortunately, there is no way to show the on-screen input from native code.
// Therefore, we call ShowSoftKeyboardInput() of the main activity implemented
// in MainActivity.kt via JNI.
#ifdef __ANDROID__
static int ShowSoftKeyboardInput(struct android_app *app) {
  JavaVM *java_vm = app->activity->vm;
  JNIEnv *java_env = NULL;

  jint jni_return = java_vm->GetEnv((void **)&java_env, JNI_VERSION_1_6);
  if (jni_return == JNI_ERR)
    return -1;

  jni_return = java_vm->AttachCurrentThread(&java_env, NULL);
  if (jni_return != JNI_OK)
    return -2;

  jclass native_activity_clazz = java_env->GetObjectClass(app->activity->clazz);
  if (native_activity_clazz == NULL)
    return -3;

  jmethodID method_id =
      java_env->GetMethodID(native_activity_clazz, "showSoftInput", "()V");
  if (method_id == NULL)
    return -4;

  java_env->CallVoidMethod(app->activity->clazz, method_id);

  jni_return = java_vm->DetachCurrentThread();
  if (jni_return != JNI_OK)
    return -5;

  return 0;
}

#endif

namespace OpenGL {
static unsigned int GetTypeSize(unsigned int type) {
  switch (type) {
  case GL_FLOAT:
    return 4;
  case GL_UNSIGNED_INT:
    return 4;
  case GL_UNSIGNED_BYTE:
    return 1;
  default:
    return -1;
  }
}

static bool glHandleError(const char *function, const char *file, int line) {
  while (GLenum error = glGetError()) {
    LOG(LOG_ERROR, "OpenGL", "[OpenGL error] ( %x ) %s  %s : %d", error, function, file, line);
    return false;
  }
  return true;
}

} // namespace OpenGL

// Unfortunately, the native KeyEvent implementation has no getUnicodeChar()
// function. Therefore, we implement the processing of KeyEvents in
// MainActivity.kt and poll the resulting Unicode characters here via JNI and
// send them to Dear ImGui.
// static int PollUnicodeChars()
//{
//    JavaVM* java_vm = g_App->activity->vm;
//    JNIEnv* java_env = NULL;
//
//    jint jni_return = java_vm->GetEnv((void**)&java_env, JNI_VERSION_1_6);
//    if (jni_return == JNI_ERR)
//        return -1;
//
//    jni_return = java_vm->AttachCurrentThread(&java_env, NULL);
//    if (jni_return != JNI_OK)
//        return -2;
//
//    jclass native_activity_clazz =
//    java_env->GetObjectClass(g_App->activity->clazz); if
//    (native_activity_clazz == NULL)
//        return -3;
//
//    jmethodID method_id = java_env->GetMethodID(native_activity_clazz,
//    "pollUnicodeChar", "()I"); if (method_id == NULL)
//        return -4;
//
//    // Send the actual characters to Dear ImGui
//    ImGuiIO& io = ImGui::GetIO();
//    jint unicode_character;
//    while ((unicode_character =
//    java_env->CallIntMethod(g_App->activity->clazz, method_id)) != 0)
//        io.AddInputCharacter(unicode_character);
//
//    jni_return = java_vm->DetachCurrentThread();
//    if (jni_return != JNI_OK)
//        return -5;
//
//    return 0;
//}

} // namespace Utility
