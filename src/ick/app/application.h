﻿#pragma once

//	Macの場合
//		DisplayLinkでフレームを同期する。
//		遅延する場合は全速で回す。
//		間に合う場合、次の開始をDisplayLinkが来るまで待機する。

#include "application_platform.h"
#include "../thread/mutex.h"

#ifdef ICK_ANDROID
struct ANativeWindow;
#endif

namespace ick{
	class ApplicationController;
	class TaskQueueThread;
	class AndroidHandler;
	
#ifdef ICK_APP_GLFW
	int ApplicationGLFWMain(int argc, const char * argv [], ApplicationController * (*controller_constructor)() );
#endif
	
	class Application {
	private:
		ApplicationController * controller_;
		bool controller_release_;
		
		bool update_running_;
		
		TaskQueueThread * render_thread_;
		
		Mutex mutex_;
		Mutex render_mutex_;

#ifdef ICK_APP_GLFW
		GLFWwindow * glfw_window_;
#endif
		
#ifdef ICK_ANDROID
		JavaVM * android_vm_;
		JNIEnv * android_env_;
		jobject android_activity_;
		bool android_activity_resumed_;
		
		EGLDisplay android_egl_display_;
		EGLConfig  android_egl_config_;
		EGLContext android_egl_context_;
		EGLSurface android_egl_surface_;

		
		AndroidHandler * main_thread_;
		bool android_update_task_posting_;
		
		bool android_render_task_posting_;
		
#endif

	public:
		Application(ApplicationController * controller, bool controller_release);
		virtual ~Application();
	
		ApplicationController * controller() const;
		
#ifdef ICK_APP_GLFW
		GLFWwindow * glfw_window() const;
		void GLFWMain();
#endif
#ifdef ICK_ANDROID
		void AndroidSetEnv(JNIEnv * env, jobject activity);
		
		void AndroidOnCreate();
		void AndroidOnDestroy();
		void AndroidOnResume();
		void AndroidOnPause();
		void AndroidOnSurfaceCreated(ANativeWindow * surface);
		void AndroidOnSurfaceChanged(ANativeWindow * surface, int format, int width, int height);
		void AndroidOnSurfaceDestroyed(ANativeWindow * surface);
		
		void AndroidStartUpdate();
		void AndroidStopUpdate();
		
		void AndroidPostUpdateTask(double delay);
		void AndroidUpdateTask();
		void AndroidUpdate();
		
		void AndroidRenderThreadInitialize();
		void AndroidRenderThreadFinalize();
		void AndroidPostRenderTask();
		void AndroidRenderTask();
		
		void AndroidRenderFinishedTask();
		
		void AndroidEGLMakeCurrent();
		void AndroidEGLClearCurrent();
		void AndroidReleaseEGLSurface();
#endif

	private:

	};
}

