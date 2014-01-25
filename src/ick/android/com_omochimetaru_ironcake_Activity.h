/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_omochimetaru_ironcake_Activity */

#ifndef _Included_com_omochimetaru_ironcake_Activity
#define _Included_com_omochimetaru_ironcake_Activity
#ifdef __cplusplus
extern "C" {
#endif
#undef com_omochimetaru_ironcake_Activity_MODE_PRIVATE
#define com_omochimetaru_ironcake_Activity_MODE_PRIVATE 0L
#undef com_omochimetaru_ironcake_Activity_MODE_WORLD_READABLE
#define com_omochimetaru_ironcake_Activity_MODE_WORLD_READABLE 1L
#undef com_omochimetaru_ironcake_Activity_MODE_WORLD_WRITEABLE
#define com_omochimetaru_ironcake_Activity_MODE_WORLD_WRITEABLE 2L
#undef com_omochimetaru_ironcake_Activity_MODE_APPEND
#define com_omochimetaru_ironcake_Activity_MODE_APPEND 32768L
#undef com_omochimetaru_ironcake_Activity_MODE_MULTI_PROCESS
#define com_omochimetaru_ironcake_Activity_MODE_MULTI_PROCESS 4L
#undef com_omochimetaru_ironcake_Activity_MODE_ENABLE_WRITE_AHEAD_LOGGING
#define com_omochimetaru_ironcake_Activity_MODE_ENABLE_WRITE_AHEAD_LOGGING 8L
#undef com_omochimetaru_ironcake_Activity_BIND_AUTO_CREATE
#define com_omochimetaru_ironcake_Activity_BIND_AUTO_CREATE 1L
#undef com_omochimetaru_ironcake_Activity_BIND_DEBUG_UNBIND
#define com_omochimetaru_ironcake_Activity_BIND_DEBUG_UNBIND 2L
#undef com_omochimetaru_ironcake_Activity_BIND_NOT_FOREGROUND
#define com_omochimetaru_ironcake_Activity_BIND_NOT_FOREGROUND 4L
#undef com_omochimetaru_ironcake_Activity_BIND_ABOVE_CLIENT
#define com_omochimetaru_ironcake_Activity_BIND_ABOVE_CLIENT 8L
#undef com_omochimetaru_ironcake_Activity_BIND_ALLOW_OOM_MANAGEMENT
#define com_omochimetaru_ironcake_Activity_BIND_ALLOW_OOM_MANAGEMENT 16L
#undef com_omochimetaru_ironcake_Activity_BIND_WAIVE_PRIORITY
#define com_omochimetaru_ironcake_Activity_BIND_WAIVE_PRIORITY 32L
#undef com_omochimetaru_ironcake_Activity_BIND_IMPORTANT
#define com_omochimetaru_ironcake_Activity_BIND_IMPORTANT 64L
#undef com_omochimetaru_ironcake_Activity_BIND_ADJUST_WITH_ACTIVITY
#define com_omochimetaru_ironcake_Activity_BIND_ADJUST_WITH_ACTIVITY 128L
#undef com_omochimetaru_ironcake_Activity_CONTEXT_INCLUDE_CODE
#define com_omochimetaru_ironcake_Activity_CONTEXT_INCLUDE_CODE 1L
#undef com_omochimetaru_ironcake_Activity_CONTEXT_IGNORE_SECURITY
#define com_omochimetaru_ironcake_Activity_CONTEXT_IGNORE_SECURITY 2L
#undef com_omochimetaru_ironcake_Activity_CONTEXT_RESTRICTED
#define com_omochimetaru_ironcake_Activity_CONTEXT_RESTRICTED 4L
#undef com_omochimetaru_ironcake_Activity_RESULT_CANCELED
#define com_omochimetaru_ironcake_Activity_RESULT_CANCELED 0L
#undef com_omochimetaru_ironcake_Activity_RESULT_OK
#define com_omochimetaru_ironcake_Activity_RESULT_OK -1L
#undef com_omochimetaru_ironcake_Activity_RESULT_FIRST_USER
#define com_omochimetaru_ironcake_Activity_RESULT_FIRST_USER 1L
#undef com_omochimetaru_ironcake_Activity_DEFAULT_KEYS_DISABLE
#define com_omochimetaru_ironcake_Activity_DEFAULT_KEYS_DISABLE 0L
#undef com_omochimetaru_ironcake_Activity_DEFAULT_KEYS_DIALER
#define com_omochimetaru_ironcake_Activity_DEFAULT_KEYS_DIALER 1L
#undef com_omochimetaru_ironcake_Activity_DEFAULT_KEYS_SHORTCUT
#define com_omochimetaru_ironcake_Activity_DEFAULT_KEYS_SHORTCUT 2L
#undef com_omochimetaru_ironcake_Activity_DEFAULT_KEYS_SEARCH_LOCAL
#define com_omochimetaru_ironcake_Activity_DEFAULT_KEYS_SEARCH_LOCAL 3L
#undef com_omochimetaru_ironcake_Activity_DEFAULT_KEYS_SEARCH_GLOBAL
#define com_omochimetaru_ironcake_Activity_DEFAULT_KEYS_SEARCH_GLOBAL 4L
/*
 * Class:     com_omochimetaru_ironcake_Activity
 * Method:    nativeStaticInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeStaticInit
  (JNIEnv *, jclass);

/*
 * Class:     com_omochimetaru_ironcake_Activity
 * Method:    nativeOnCreate
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnCreate
  (JNIEnv *, jobject);

/*
 * Class:     com_omochimetaru_ironcake_Activity
 * Method:    nativeOnDestroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnDestroy
  (JNIEnv *, jobject);

/*
 * Class:     com_omochimetaru_ironcake_Activity
 * Method:    nativeOnResume
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnResume
  (JNIEnv *, jobject);

/*
 * Class:     com_omochimetaru_ironcake_Activity
 * Method:    nativeOnPause
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnPause
  (JNIEnv *, jobject);

/*
 * Class:     com_omochimetaru_ironcake_Activity
 * Method:    surfaceCreated
 * Signature: (Landroid/view/SurfaceHolder;)V
 */
JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_surfaceCreated
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_omochimetaru_ironcake_Activity
 * Method:    surfaceChanged
 * Signature: (Landroid/view/SurfaceHolder;III)V
 */
JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_surfaceChanged
  (JNIEnv *, jobject, jobject, jint, jint, jint);

/*
 * Class:     com_omochimetaru_ironcake_Activity
 * Method:    surfaceDestroyed
 * Signature: (Landroid/view/SurfaceHolder;)V
 */
JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_surfaceDestroyed
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
