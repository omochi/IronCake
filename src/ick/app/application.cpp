#include "application.h"

#include "../base/memory.h"
#include "../base/abort.h"
#include "../base/time.h"
#include "../function/function.h"
#include "../thread/scoped_lock.h"
#include "../thread/loop_thread.h"

#ifdef ICK_WINDOWS
#	include "../windows/error.h"
#	include "../windows/wait.h"
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

#ifdef ICK_WINDOWS

	void Application::WinSetupUpdateTimer(){
		win_update_timer_queue_ = CreateTimerQueue();
		if (!win_update_timer_queue_){
			ICK_ABORT("CreateTimerQueue: %s\n", WindowsLastErrorGetDescription().cstr());
		}
		if (!CreateTimerQueueTimer(&win_update_timer_,
			win_update_timer_queue_,
			ApplicationWinUpdateTimerCallback,
			static_cast<VOID *>(this),
			0, 16,
			WT_EXECUTEDEFAULT)){
			ICK_ABORT("CreateTimerQueueTimer: %s\n", WindowsLastErrorGetDescription().cstr());
		}
	}
	void Application::WinTeardownUpdateTimer(){
		HANDLE wait_event = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (!wait_event){
			ICK_ABORT("CreateEvent(timer wait): %s\n", WindowsLastErrorGetDescription().cstr());
		}

		if (!DeleteTimerQueueTimer(win_update_timer_queue_, win_update_timer_,wait_event)){
			ICK_ABORT("DeleteTimerQueueTimer: %s\n", WindowsLastErrorGetDescription().cstr());
		}

		DWORD wait_ret = WaitForSingleObject(wait_event, INFINITE);
		if (WindowsWaitResultGetObjectIndex(wait_ret, 1) == -1){
			ICK_ABORT("Wait: %s\n",WindowsWaitResultGetDescription(wait_ret, 1).cstr());
		}

		if (!CloseHandle(wait_event)){
			ICK_ABORT("CloseHandle(timer wait): %s\n", WindowsLastErrorGetDescription().cstr());
		}

		if (!DeleteTimerQueue(win_update_timer_queue_)){
			ICK_ABORT("DeleteTimerQueue: %s\n", WindowsLastErrorGetDescription().cstr());
		}
	}

	VOID NTAPI ApplicationWinUpdateTimerCallback(PVOID lpParameter, BOOLEAN TimerOrWaitFired){
		Application * thiz = static_cast<Application *>(lpParameter);
		thiz->SignalUpdateTime();
	}

#endif

	Application::Application(ApplicationController * controller, bool controller_release):
	controller_(controller),controller_release_(controller_release),
	running_(false)
	{
		ICK_ASSERT(controller);
		controller_->application_ = this;
		
#ifdef ICK_APP_GLFW
		glfw_do_window_create_ = false;
		glfw_window_ = NULL;
#endif
		
#ifdef ICK_ANDROID
		android_egl_display_ = NULL;
		android_egl_context_ = NULL;
		android_egl_surface_ = NULL;
#endif
		
		master_thread_ = ICK_NEW(LoopThread);
		master_thread_->set_name(String("master"));
		master_thread_->Start();
	}
	
	Application::~Application(){
		if(running_){ ICK_ABORT("has not terminated\n"); }
		
		master_thread_->PostQuit();
		master_thread_->Join();
		ICK_DELETE(master_thread_);
		
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
		
		while(true){
			
			if(glfw_do_window_create_){
				glfw_do_window_create_ = false;
				
				glfwWindowHint(GLFW_RESIZABLE, 0);
				glfw_window_ = glfwCreateWindow(640, 480, "IronCake GL Test", NULL, NULL);
				if (!glfw_window_){ ICK_ABORT("glfwCreateWindow\n"); }
				
				glfwMakeContextCurrent(glfw_window_);
				controller_->DidInitGL();
			}
			
			if(!glfw_window_){ break; }
			
			while (!glfwWindowShouldClose(glfw_window_)){
				glfwPollEvents();
				
				controller_->OnUpdate();
				controller_->OnRender();
				
				glfwSwapBuffers(glfw_window_);
			}
			
			controller_->WillReleaseGL();
			glfwDestroyWindow(glfw_window_);
			glfw_window_ = NULL;
		}
		
		controller_->WillTerminate();
		
		glfwTerminate();
	}

#endif
	
#ifdef ICK_ANDROID
	void Application::AndroidOnCreate(){
		
		//ユーザinit
		
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
		
		if(android_egl_context_){ ICK_ABORT("egl context already created\n"); }
		EGLint choose_attribs[] = {
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
		if(eglDestroyContext(android_egl_display_, android_egl_context_) == EGL_FALSE){
			ICK_ABORT("eglDestroyContext failed\n");
		}
		
		if(eglTerminate(android_egl_display_) == EGL_FALSE){
			ICK_ABORT("eglTerminate failed\n");
		}
		android_egl_display_ = NULL;
	}
	void Application::AndroidOnResume(){
		
	}
	void Application::AndroidOnPause(){
		
	}
	void Application::AndroidOnSurfaceAvailable(jobject surface_texture, int width, int height){
		if(android_egl_surface_){ ICK_ABORT("surface already available\n"); }
		//EGL初期化
	}
	void Application::AndroidOnSurfaceSizeChanged(jobject surface_texture, int width, int height){
		//EGLSurface交換
	}
	void Application::AndroidOnSurfaceDestroyed(jobject surface_texture){
		if(android_egl_context_){
			
		}
	}
#endif
	
	void Application::RequestGLInit(){
#ifdef ICK_APP_GLFW
		glfw_do_window_create_ = true;
#endif
	}
	void Application::RequestGLRelease(){
#ifdef ICK_APP_GLFW
		glfwSetWindowShouldClose(glfw_window_, 1);
#endif
	}
	
	void Application::Launch(){
		master_thread_->Post(FunctionMake(this, &Application::DoLaunch));
		{
			ICK_SCOPED_LOCK(running_mutex_);
			while(!running_){ running_mutex_.Wait(); }
		}
	}
	void Application::Terminate(){
		master_thread_->Post(FunctionMake(this, &Application::DoTerminate));
		{
			ICK_SCOPED_LOCK(running_mutex_);
			while(running_){ running_mutex_.Wait(); }
		}
	}
	
	void Application::SignalUpdateTime(){
		ICK_SCOPED_LOCK(update_mutex_);
		
		if(update_running_){
			update_deadline_missed_ = true;
		}else{
			RequestUpdate();
		}
	}
	
	void Application::RequestUpdate(){
		ICK_SCOPED_LOCK(update_mutex_);
		update_running_ = true;
		update_deadline_missed_ = false;
		
		master_thread_->Post(FunctionMake(this, &Application::Update));
	}
	
	void Application::RequestRender(){
		ICK_SCOPED_LOCK(render_mutex_);
		render_running_ = true;
	
		render_thread_->Post(FunctionMake(this, &Application::Render));
	}
	
	void Application::DoLaunch(){
		if(running_){ ICK_ABORT("already launched\n"); }
		update_running_ = false;
		update_deadline_missed_ = false;
		render_running_ = false;
		
		render_thread_ = ICK_NEW(LoopThread);
		render_thread_->set_name(String("render"));
		render_thread_->Start();
		render_thread_->Post(FunctionMake(this, &Application::InitRender));
		
#ifdef ICK_MAC
		MacSetupDisplayLink();
#endif
#ifdef ICK_WINDOWS
		WinSetupUpdateTimer();
#endif
		
		{
			ICK_SCOPED_LOCK(running_mutex_);
			running_ = true;
			running_mutex_.Broadcast();
		}
		
		controller_->DidLaunch();
	}
	
	void Application::DoTerminate(){
		if(!running_){ ICK_ABORT("has not launched\n"); }
		
		controller_->WillTerminate();
		
#ifdef ICK_MAC
		MacTeardownDisplayLink();
#endif
#ifdef ICK_WINDOWS
		WinTeardownUpdateTimer();
#endif
		
		render_thread_->PostQuit();
		render_thread_->Join();
		ICK_DELETE(render_thread_);
		
		{
			ICK_SCOPED_LOCK(running_mutex_);
			running_ = false;
			running_mutex_.Broadcast();
		}
	}
	
	void Application::Update(){
		{
			ICK_SCOPED_LOCK(running_mutex_);
			if(!running_){ return; }
		}
		
		controller_->OnUpdate();
		
		{
			ICK_SCOPED_LOCK(render_mutex_);
			RequestRender();
			while(render_running_){ render_mutex_.Wait(); }
		}

		{
			ICK_SCOPED_LOCK(update_mutex_);
			if(update_deadline_missed_){
				RequestUpdate();
			}else{
				update_running_ = false;
			}
		}
	}
	
	void Application::InitRender(){
#ifdef ICK_APP_GLFW
		glfwSwapInterval(0);
		glfwMakeContextCurrent(glfw_window_);
#endif
	}
	
	void Application::Render(){
		controller_->OnRender();
		
#ifdef ICK_APP_GLFW
		glfwSwapBuffers(glfw_window_);
#endif
		{
			ICK_SCOPED_LOCK(render_mutex_);
			render_running_ = false;
			render_mutex_.Broadcast();
		}
	}
	
}

#endif
