#pragma once

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
		
#ifdef ICK_APP_GLFW
	int ApplicationGLFWMain(int argc, const char * argv [], ApplicationController * (*controller_constructor)() );
#endif
	
	class Application {
	private:
		ApplicationController * controller_;
		bool controller_release_;
		
		bool update_running_;

#ifdef ICK_APP_GLFW
		GLFWwindow * glfw_window_;
#endif
		
#ifdef ICK_ANDROID
		JNIEnv * android_env_;
		jobject android_activity_;
		bool android_activity_resumed_;
		
		EGLDisplay android_egl_display_;
		EGLConfig  android_egl_config_;
		EGLContext android_egl_context_;
		EGLSurface android_egl_surface_;
		
		jobject android_posting_update_task_;
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
		void AndroidUpdateTask(JNIEnv * env, jobject task);
		void AndroidUpdate();
		
		void AndroidSetEnv(JNIEnv * env, jobject activity);
		void AndroidReleaseEGLSurface();
#endif

		void Launch();
		void Terminate();
	private:
#ifdef ICK_ANDROID
		void AndroidReleaseEGL();
#endif

	};
}

