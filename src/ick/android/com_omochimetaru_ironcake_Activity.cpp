#include "com_omochimetaru_ironcake_Activity.h"

#include <android/log.h>

#include "../base/memory.h"
#include "../base/log.h"
#include "../app/application.h"
#include "../startup.h"

namespace ick{
	namespace jni{
		jmethodID activity_controller_construct_method;
		jfieldID activity_application_field;
	}
}


#ifdef __cplusplus
extern "C" {
#endif
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeStaticInit
	(JNIEnv * env, jclass thiz){
		jclass activity_class = env->FindClass("com/omochimetaru/ironcake/Activity");
		ick::jni::activity_controller_construct_method =
		env->GetMethodID(activity_class, "controllerConstruct", "()J");
		ick::jni::activity_application_field =
		env->GetFieldID(activity_class, "application", "J");
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnCreate
	(JNIEnv * env, jobject thiz){
		if(ick::IsStartedup()){
			__android_log_print(ANDROID_LOG_ERROR, "IronCake", "IronCake already startedup. 2 Activities may be created.");
			::abort();
		}
		if(!ick::Startup()){
			__android_log_print(ANDROID_LOG_ERROR, "IronCake", "ick::Startup failed");
			::abort();
		}
		
		jlong controller = env->CallLongMethod(thiz, ick::jni::activity_controller_construct_method);
		ick::Application * app = ICK_NEW(ick::Application, reinterpret_cast<ick::ApplicationController *>(controller), true);
		env->SetLongField(thiz, ick::jni::activity_application_field, reinterpret_cast<jlong>(app));
		
		app->AndroidOnCreate();
		
		ICK_LOG_INFO("nativeOnCreate");
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnDestroy
	(JNIEnv * env, jobject thiz){
		ICK_LOG_INFO("nativeOnDestroy");
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity_application_field));
		
		app->AndroidOnDestroy();
		
		ICK_DELETE(app);
		
		env->SetLongField(thiz, ick::jni::activity_application_field, 0);
		
		if(!ick::Shutdown()){
			__android_log_print(ANDROID_LOG_ERROR, "IronCake", "ick::Shutdown failed");
			::abort();
		}
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnResume
	(JNIEnv * env, jobject thiz){
		ICK_LOG_INFO("nativeOnResume");
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity_application_field));
		app->AndroidOnResume();
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnPause
	(JNIEnv * env, jobject thiz){
		ICK_LOG_INFO("nativeOnPause");
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity_application_field));
		app->AndroidOnPause();
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnSurfaceTextureAvailable
	(JNIEnv * env, jobject thiz, jobject surfaceTexture, jint width, jint height){
		__android_log_print(ANDROID_LOG_INFO, "IronCake", "nativeOnSurfaceTextureAvailable: %p, %d x %d", surfaceTexture, width, height);
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity_application_field));
		if(app){
			app->AndroidOnSurfaceAvailable(surfaceTexture, width, height);
		}
	}
	
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnSurfaceTextureSizeChanged
	(JNIEnv * env, jobject thiz, jobject surfaceTexture, jint width, jint height){
		__android_log_print(ANDROID_LOG_INFO, "IronCake", "nativeOnSurfaceTextureSizeChanged: %p, %d x %d", surfaceTexture, width, height);
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity_application_field));
		if(app){
			app->AndroidOnSurfaceSizeChanged(surfaceTexture, width, height);
		}
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnSurfaceTextureDestroyed
	(JNIEnv * env, jobject thiz, jobject surfaceTexture){
		__android_log_print(ANDROID_LOG_INFO, "IronCake", "nativeOnSurfaceTextureDestroyed: %p", surfaceTexture);
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity_application_field));
		if(app){
			//Activity.onDestroyが済んでいる場合がある
			app->AndroidOnSurfaceDestroyed(surfaceTexture);
		}
	}
	
#ifdef __cplusplus
}
#endif
