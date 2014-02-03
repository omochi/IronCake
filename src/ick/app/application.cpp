#include "application.h"

#include "../base/memory.h"
#include "../base/abort.h"
#include "../base/time.h"
#include "../base/math.h"
#include "../function/function.h"
#include "../thread/scoped_lock.h"
#include "../thread/task_queue_thread.h"

#ifdef ICK_WINDOWS
#	include "../windows/error.h"
#	include "../windows/wait.h"
#endif

#ifdef ICK_ANDROID
#	include "../android/activity.h"
#	include "../android/native_task.h"
#	include "../android/android_handler.h"
#endif

#include "application_controller.h"

#include "../startup.h"

#ifdef ICK_OBJCPP_GUARD

namespace ick{
	
#ifdef ICK_APP_GLFW
	int ApplicationGLFWMain(int argc, const char * argv [], ApplicationController * (*controller_constructor)() )
	{
		(void)argc; (void)argv;
		
		if(!ick::Startup()){
			::fprintf(stderr,"ick::Startup failed\n");
			return EXIT_FAILURE;
		}
		
		ick::Application * app = ICK_NEW(ick::Application, controller_constructor(), true);
		app->GLFWMain();
		ICK_DELETE(app);
		
		if(!ick::Shutdown()){
			::fprintf(stderr, "ick::Shutdown failed\n");
			return EXIT_FAILURE;
		}
		
		return EXIT_SUCCESS;
	}
#endif

	Application::Application(ApplicationController * controller, bool controller_release):
	controller_(controller),controller_release_(controller_release)
	{
		ICK_ASSERT(controller);
		controller_->application_ = this;
		
		update_running_ = false;
		
		render_thread_ = NULL;
		
#ifdef ICK_APP_GLFW
		glfw_window_ = NULL;
#endif
		
#ifdef ICK_ANDROID
		android_env_         = NULL;
		android_activity_    = NULL;
		android_activity_resumed_ = false;
		android_egl_display_ = NULL;
		android_egl_config_  = NULL;
		android_egl_context_ = NULL;
		android_egl_surface_ = NULL;
		
		main_thread_ = NULL;
		android_update_task_posting_ = false;
		
		android_render_task_posting_ = false;
#endif

	}
	
	Application::~Application(){		
		ick::PropertyClear(controller_, controller_release_);
	}
	
	ApplicationController * Application::controller() const{
		return controller_;
	}
		
#ifdef ICK_APP_GLFW

	GLFWwindow * Application::glfw_window() const{
		return glfw_window_;
	}
	
	void Application::GLFWMain(){
		if (!glfwInit()){ ICK_ABORT("glfwInit\n"); }
		
		controller_->DidLaunch();
		
		glfwWindowHint(GLFW_RESIZABLE, 0);
		glfw_window_ = glfwCreateWindow(640, 480, "IronCake GL Test", NULL, NULL);
		if (!glfw_window_){ ICK_ABORT("glfwCreateWindow\n"); }
		
		glfwMakeContextCurrent(glfw_window_);
		controller_->DidInitGL();
	
		while (!glfwWindowShouldClose(glfw_window_)){
			glfwPollEvents();
			
			controller_->OnUpdate();
			controller_->OnRender();
			
			glfwSwapBuffers(glfw_window_);
		}
		
		controller_->WillReleaseGL();
		
		glfwMakeContextCurrent(NULL);
		
		glfwDestroyWindow(glfw_window_);
		glfw_window_ = NULL;
		
		controller_->WillTerminate();
		
		glfwTerminate();
	}

#endif
	
#ifdef ICK_ANDROID
	void Application::AndroidSetEnv(JNIEnv * env, jobject activity){
		if(android_env_){
			android_env_->DeleteGlobalRef(android_activity_);
			android_activity_ = NULL;
			android_env_ = NULL;
		}
		android_vm_ = NULL;
		if(env){
			android_env_ = env;
			android_activity_ = env->NewGlobalRef(activity);
			
			if(env->GetJavaVM(&android_vm_)){ ICK_ABORT("GetJavaVM failed\n"); }
		}
	}

	void Application::AndroidOnCreate(){
		
		jobject main_thread_handler = android_env_->GetObjectField(android_activity_, jni::activity::main_thread_handler_field);
		main_thread_ = ICK_NEW(AndroidHandler, android_env_, main_thread_handler);
		
		render_thread_ = ICK_NEW(TaskQueueThread);
		render_thread_->Start();
		render_thread_->PostTask(FunctionMake(this, &Application::AndroidRenderThreadInitialize));
		
		controller_->DidLaunch();
		
		if(android_egl_display_){ ICK_ABORT("egl display already initialized\n"); }
		EGLDisplay egl_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		if(egl_display == EGL_NO_DISPLAY){
			ICK_ABORT("eglGetDisplay failed\n");
		}
		EGLint major, minor;
		if(eglInitialize(egl_display, & major, & minor) == EGL_FALSE){
			ICK_ABORT("eglInitialize failed\n");
		}
		ICK_LOG_INFO("egl initialized. version: %d.%d\n", major, minor);
		android_egl_display_ = egl_display;
		
		if(android_egl_config_){ ICK_ABORT("egl config already created\n"); }
		EGLint choose_attribs[] = {
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_RED_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_BLUE_SIZE, 8,
			EGL_ALPHA_SIZE, 8,
			EGL_DEPTH_SIZE, 16,
			EGL_STENCIL_SIZE, 8,
			EGL_NONE
		};
		EGLConfig configs[1];
		EGLint configs_num;
		if(eglChooseConfig(android_egl_display_, choose_attribs,
						   configs,ICK_ARRAY_SIZE(configs),&configs_num) == EGL_FALSE)
		{
			ICK_ABORT("eglChooseConfig failed\n");
		}
		if(configs_num == 0){ ICK_ABORT("no egl config returned\n"); }
		android_egl_config_ = configs[0];
		
		if(android_egl_context_){ ICK_ABORT("egl context already created\n"); }
		EGLint context_attribs[] = {
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
		};
		EGLContext egl_context = eglCreateContext(egl_display, configs[0], NULL, context_attribs);
		if(egl_context == EGL_NO_CONTEXT){
			ICK_ABORT("eglCreateContext failed\n");
		}
		android_egl_context_ = egl_context;

	}
	void Application::AndroidOnDestroy(){
		if(!android_egl_display_){ ICK_ABORT("egl display has not been initialized\n"); }
		if(!android_egl_context_){ ICK_ABORT("egl context has not been created\n"); }
		
		controller_->WillTerminate();
		
		if(android_egl_surface_){
			AndroidReleaseEGLSurface();
		}
		
		if(eglDestroyContext(android_egl_display_, android_egl_context_) == EGL_FALSE){
			ICK_ABORT("eglDestroyContext failed\n");
		}
		
		if(eglTerminate(android_egl_display_) == EGL_FALSE){
			ICK_ABORT("eglTerminate failed\n");
		}
		android_egl_display_ = NULL;
		
		render_thread_->PostTask(FunctionMake(this, &Application::AndroidRenderThreadFinalize));
		render_thread_->PostQuit();
		render_thread_->Join();
		ick::PropertyClear(render_thread_);
		
		android_update_task_posting_ = false;
		ick::PropertyClear(main_thread_);
		
		AndroidSetEnv(NULL, NULL);
	}
	void Application::AndroidOnResume(){
		android_activity_resumed_ = true;
		
		if(android_egl_surface_){
			AndroidStartUpdate();
		}
	}
	void Application::AndroidOnPause(){
		if(update_running_){
			AndroidStopUpdate();
		}
		
		android_activity_resumed_ = false;
	}
	void Application::AndroidOnSurfaceCreated(ANativeWindow * surface){
		if(android_egl_surface_){ ICK_ABORT("surface already available\n"); }
		
		EGLSurface egl_surface = eglCreateWindowSurface(android_egl_display_,
														android_egl_config_,
														surface,
														NULL);
		if(egl_surface == EGL_NO_SURFACE){
			ICK_ABORT("eglCreateWindowSurface failed\n");
		}
		android_egl_surface_ = egl_surface;
		
		AndroidEGLMakeCurrent();

		controller_->DidInitGL();
		
		AndroidEGLClearCurrent();
				
		if(android_activity_resumed_){
			AndroidStartUpdate();
		}
	}
	void Application::AndroidOnSurfaceChanged(ANativeWindow * surface, int format, int width, int height){
		ICK_LOG_INFO("SurfaceChanged: %d x %d", width, height);
	}
	void Application::AndroidOnSurfaceDestroyed(ANativeWindow * surface){
		if(update_running_){
			AndroidStopUpdate();
		}
		
		if(android_egl_surface_){
			AndroidReleaseEGLSurface();
		}
	}
	

	void Application::AndroidStartUpdate(){
		if(update_running_){ ICK_ABORT("update is already running\n"); }
		if(!android_activity_resumed_){ ICK_ABORT("activity is not resumed\n"); }
		if(!android_egl_surface_){ ICK_ABORT("egl surface is not created\n"); }
		
		update_running_ = true;
		
		if(!android_update_task_posting_){
			AndroidPostUpdateTask(0.0);
		}
	}
	void Application::AndroidStopUpdate(){
		if(!update_running_){ ICK_ABORT("update is not running\n"); }

		update_running_ = false;
		android_update_task_posting_ = false;
	}
	
	void Application::AndroidPostUpdateTask(double delay){
		android_update_task_posting_ = true;
		main_thread_->PostTask(FunctionMake(this, &Application::AndroidUpdateTask));
	}

	void Application::AndroidUpdateTask(){
		ICK_LOG_INFO("%s\n", __func__);
		if(android_update_task_posting_){
			android_update_task_posting_ = false;
			AndroidUpdate();
		}

	}
	
	void Application::AndroidUpdate(){
		AndroidEGLMakeCurrent();
		
		controller_->OnUpdate();
		
		AndroidEGLClearCurrent();

		AndroidPostRenderTask();
	}
	
	void Application::AndroidRenderThreadInitialize(){
		ICK_LOG_INFO("%s\n", __func__);
		JNIEnv * env;
		if(android_vm_->AttachCurrentThread(&env, NULL) != JNI_OK){
			ICK_ABORT("jni AttachCurrentThread failed\n");
		}
	}
	void Application::AndroidRenderThreadFinalize(){
		ICK_LOG_INFO("%s\n", __func__);
		if(android_vm_->DetachCurrentThread() != JNI_OK){
			ICK_ABORT("jni DetachCurrentThread failed\n");
		}
	}
	
	
	void Application::AndroidPostRenderTask(){
		ICK_SCOPED_LOCK(mutex_);
		android_render_task_posting_ = true;
		render_thread_->PostTask(FunctionMake(this, &Application::AndroidRenderTask));
	}
	
	void Application::AndroidRenderTask(){
		//ICK_LOG_INFO("%s\n", __func__);
		AndroidEGLMakeCurrent();
		
		controller_->OnRender();
		
		if(eglSwapBuffers(android_egl_display_, android_egl_surface_) == EGL_FALSE){
			ICK_ABORT("eglSwapBuffers failed 0x%04x\n", eglGetError());
		}
		
		AndroidEGLClearCurrent();
		
		{
			ICK_SCOPED_LOCK(mutex_);
			android_render_task_posting_ = false;
			mutex_.Broadcast();
		}
		
		main_thread_->PostTask(FunctionMake(this, &Application::AndroidRenderFinishedTask));
	}
	
	void Application::AndroidRenderFinishedTask(){
		if(update_running_){
			AndroidUpdate();
		}
	}
	
	void Application::AndroidEGLMakeCurrent(){
		if(eglMakeCurrent(android_egl_display_,
						  android_egl_surface_, android_egl_surface_,
						  android_egl_context_) == EGL_FALSE)
		{
			ICK_ABORT("eglMakeCurrent failed: 0x%04x\n", eglGetError());
		}
	}
	void Application::AndroidEGLClearCurrent(){
		if(eglMakeCurrent(android_egl_display_,EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) == EGL_FALSE)
		{
			ICK_ABORT("eglMakeCurrent(clear) failed\n");
		}
	}
	
	void Application::AndroidReleaseEGLSurface(){
		controller_->WillReleaseGL();
		
		AndroidEGLClearCurrent();
		
		if(eglDestroySurface(android_egl_display_, android_egl_surface_) == EGL_FALSE){
			ICK_ABORT("eglDestroySurface failed\n");
		}
		android_egl_surface_ = NULL;
	}
#endif

	
}

#endif
