#include "activity.h"

#include <stdint.h>
#include <android/log.h>
#include <android/native_window_jni.h>

#include "../base/memory.h"
#include "../base/log.h"
#include "../app/application.h"
#include "../startup.h"

namespace ick{
	namespace jni{
		namespace activity{
			jmethodID controller_construct_method;
			jmethodID schedule_update_timer_method;
			jfieldID application_field;
			jfieldID main_thread_handler_field;
			
			jmethodID surface_holder_get_surface_method;
			
			jmethodID handler_post_delayed_method;
		}
	}
}

#ifdef __cplusplus
extern "C" {
#endif
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeStaticInit
	(JNIEnv * env, jclass klass){
		using namespace ick::jni::activity;
		controller_construct_method = env->GetMethodID(klass, "controllerConstruct", "()J");
		schedule_update_timer_method = env->GetMethodID(klass, "scheduleUpdateTimer", "(F)V");
		application_field = env->GetFieldID(klass, "application", "J");
		main_thread_handler_field = env->GetFieldID(klass, "mainThreadHandler", "Landroid/os/Handler;");
		
		jclass surface_class = env->FindClass("android/view/SurfaceHolder");
		surface_holder_get_surface_method = env->GetMethodID(surface_class, "getSurface", "()Landroid/view/Surface;");
		
		jclass handler_class = env->FindClass("android/os/Handler");
		handler_post_delayed_method = env->GetMethodID(handler_class, "postDelayed", "(Ljava/lang/Runnable;J)Z");
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
		
		jlong controller = env->CallLongMethod(thiz, ick::jni::activity::controller_construct_method);
		ick::Application * app = ICK_NEW(ick::Application, reinterpret_cast<ick::ApplicationController *>(controller), true);
		env->SetLongField(thiz, ick::jni::activity::application_field, reinterpret_cast<jlong>(app));
		
		app->AndroidSetEnv(env, thiz);
		app->AndroidOnCreate();
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnDestroy
	(JNIEnv * env, jobject thiz){
		__android_log_print(ANDROID_LOG_INFO, "IronCake", "%s", __func__);
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity::application_field));
		
		app->AndroidOnDestroy();
		
		ICK_DELETE(app);
		
		env->SetLongField(thiz, ick::jni::activity::application_field, 0);
		
		if(!ick::Shutdown()){
			__android_log_print(ANDROID_LOG_ERROR, "IronCake", "ick::Shutdown failed");
			::abort();
		}
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnResume
	(JNIEnv * env, jobject thiz){
		__android_log_print(ANDROID_LOG_INFO, "IronCake", "%s", __func__);
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity::application_field));
		app->AndroidOnResume();
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_nativeOnPause
	(JNIEnv * env, jobject thiz){
		__android_log_print(ANDROID_LOG_INFO, "IronCake", "%s", __func__);
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity::application_field));
		app->AndroidOnPause();
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_surfaceCreated
	(JNIEnv * env, jobject thiz, jobject surface_holder){
		__android_log_print(ANDROID_LOG_INFO, "IronCake", "%s", __func__);
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity::application_field));
		if(app){
			jobject surface = env->CallObjectMethod(surface_holder, ick::jni::activity::surface_holder_get_surface_method);
			app->AndroidOnSurfaceCreated(ANativeWindow_fromSurface(env, surface));
		}
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_surfaceChanged
	(JNIEnv * env, jobject thiz, jobject surface_holder, jint format, jint width, jint height){
		__android_log_print(ANDROID_LOG_INFO, "IronCake", "%s", __func__);
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity::application_field));
		if(app){
			jobject surface = env->CallObjectMethod(surface_holder, ick::jni::activity::surface_holder_get_surface_method);
			app->AndroidOnSurfaceChanged(ANativeWindow_fromSurface(env, surface), format, width, height);
		}
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_surfaceDestroyed
	(JNIEnv * env, jobject thiz, jobject surface_holder){
		__android_log_print(ANDROID_LOG_INFO, "IronCake", "%s", __func__);
		
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity::application_field));
		if(app){
			//Activity.onDestroyが済んでいる場合がある
			jobject surface = env->CallObjectMethod(surface_holder, ick::jni::activity::surface_holder_get_surface_method);
			app->AndroidOnSurfaceDestroyed(ANativeWindow_fromSurface(env, surface));
		}
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_Activity_update
	(JNIEnv * env, jobject thiz){
		ick::Application * app = reinterpret_cast<ick::Application *>(env->GetLongField(thiz, ick::jni::activity::application_field));
		if(app){
			app->AndroidUpdate();
		}
	}
	
#ifdef __cplusplus
}
#endif
