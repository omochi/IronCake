#pragma once

#include <jni.h>

namespace ick{
	namespace jni{
		namespace activity{
			extern jmethodID controller_construct_method;
			extern jfieldID application_field;
			extern jfieldID main_thread_handler_field;
			
			extern jmethodID surface_holder_get_surface_method;
			
			extern jmethodID handler_post_delayed_method;
		}
	}
}

#ifdef __cplusplus
extern "C" {
#endif

	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeStaticInit
	(JNIEnv * env, jclass klass);
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnCreate
	(JNIEnv * env, jobject thiz);
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnDestroy
	(JNIEnv * env, jobject thiz);
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnResume
	(JNIEnv * env, jobject thiz);
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnPause
	(JNIEnv * env, jobject thiz);
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_surfaceCreated
	(JNIEnv * env, jobject thiz, jobject surface_holder);
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_surfaceChanged
	(JNIEnv * env, jobject thiz, jobject surface_holder, jint format, jint width, jint height);
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_surfaceDestroyed
	(JNIEnv * env, jobject thiz, jobject surface_holder);
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_update
	(JNIEnv * env, jobject thiz);

#ifdef __cplusplus
}
#endif

