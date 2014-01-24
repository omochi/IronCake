#include "com_omochimetaru_ironcake_Activity.h"

#include <android/log.h>

#include "../base/log.h"
#include "../startup.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnCreate
	(JNIEnv * env, jobject thiz){
		if(!ick::Startup()){
			__android_log_print(ANDROID_LOG_ERROR, "IronCake", "ick::Startup failed");
			::abort();
		}
		
		ICK_LOG_INFO("nativeOnCreate");
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnDestroy
	(JNIEnv * env, jobject thiz){
		ICK_LOG_INFO("nativeOnDestroy");
		
		if(!ick::Shutdown()){
			__android_log_print(ANDROID_LOG_ERROR, "IronCake", "ick::Shutdown failed");
			::abort();
		}
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnResume
	(JNIEnv * env, jobject thiz){
		ICK_LOG_INFO("nativeOnResume");
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnPause
	(JNIEnv * env, jobject thiz){
		ICK_LOG_INFO("nativeOnPause");
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnSurfaceTextureAvailable
	(JNIEnv * env, jobject thiz, jobject surfaceTexture, jint width, jint height){
		ICK_LOG_INFO("nativeOnSurfaceTextureAvailable");
	}
	
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnSurfaceTextureSizeChanged
	(JNIEnv * env, jobject thiz, jobject surfaceTexture, jint width, jint height){
		ICK_LOG_INFO("nativeOnSurfaceTextureSizeChanged");
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnSurfaceTextureDestroyed
	(JNIEnv * env, jobject thiz, jobject surfaceTexture){
		ICK_LOG_INFO("nativeOnSurfaceTextureDestroyed");
	}
	
#ifdef __cplusplus
}
#endif
