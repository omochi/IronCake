#include "com_omochimetaru_ironcake_Activity.h"

#include <stdint.h>
#include <android/log.h>
#include <android/native_window_jni.h>

#include "../base/memory.h"
#include "../base/log.h"
#include "../app/application.h"
#include "../startup.h"

namespace ick{
	namespace jni{
		jmethodID activity_controller_construct_method;
		jfieldID activity_application_field;
		
		jmethodID surface_holder_get_surface_method;
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
		
		jclass surface_class = env->FindClass("android/view/SurfaceHolder");
		ick::jni::surface_holder_get_surface_method =
		env->GetMethodID(surface_class, "getSurface", "()Landroid/view/Surface;");
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnCreate
	(JNIEnv * env, jobject thiz){
		__android_log_print(ANDROID_LOG_INFO, "IronCake", "%s", __func__);
		
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
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnDestroy
	(JNIEnv * env, jobject thiz){
		__android_log_print(ANDROID_LOG_INFO, "IronCake", "%s", __func__);
		
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
		__android_log_print(ANDROID_LOG_INFO, "IronCake", "%s", __func__);
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity_application_field));
		app->AndroidOnResume();
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnPause
	(JNIEnv * env, jobject thiz){
		__android_log_print(ANDROID_LOG_INFO, "IronCake", "%s", __func__);
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity_application_field));
		app->AndroidOnPause();
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_surfaceCreated
	(JNIEnv * env, jobject thiz, jobject surface_holder){
		__android_log_print(ANDROID_LOG_INFO, "IronCake", "%s", __func__);
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity_application_field));
		if(app){
			jobject surface = env->CallObjectMethod(surface_holder, ick::jni::surface_holder_get_surface_method);
			app->AndroidOnSurfaceCreated(ANativeWindow_fromSurface(env, surface));
		}
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_surfaceChanged
	(JNIEnv * env, jobject thiz, jobject surface_holder, jint format, jint width, jint height){
		__android_log_print(ANDROID_LOG_INFO, "IronCake", "%s", __func__);
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity_application_field));
		if(app){
			jobject surface = env->CallObjectMethod(surface_holder, ick::jni::surface_holder_get_surface_method);
			app->AndroidOnSurfaceChanged(ANativeWindow_fromSurface(env, surface), format, width, height);
		}
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_surfaceDestroyed
	(JNIEnv * env, jobject thiz, jobject surface_holder){
		__android_log_print(ANDROID_LOG_INFO, "IronCake", "%s", __func__);
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity_application_field));
		if(app){
			//Activity.onDestroyが済んでいる場合がある
			jobject surface = env->CallObjectMethod(surface_holder, ick::jni::surface_holder_get_surface_method);
			app->AndroidOnSurfaceDestroyed(ANativeWindow_fromSurface(env, surface));
		}
	}
	
#ifdef __cplusplus
}
#endif
