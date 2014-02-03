#pragma once

//	Android
//		StartUpdate,StopUpdate,Updateいずれもメインスレ。
//		StartUpdateとStopUpdateの間にしかUpdateが呼ばれない。
//		タスクはフラグを見て、折れてたら呼ばない。
//		StopするかUpdateしたらフラグを折る。
//		Startしたらフラグを立てて、2重発行はしない。
//
//		RenderはUpdateから呼ばれてレンダースレ。
//		StopUpdateでタスクキューの消化を待つ事で、
//		Start-Stop間しかRenderしないようにする。

#include "application_platform.h"
#include "../thread/mutex.h"
#include "../thread/signal.h"

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
		
		Signal android_render_finish_signal_;
		
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
		
		void AndroidPostSingleUpdateTask();
		void AndroidUpdateTask();
		void AndroidUpdate();
		
		void AndroidRenderTask();

		void AndroidEGLMakeCurrent();
		void AndroidEGLClearCurrent();
		void AndroidReleaseEGLSurface();
#endif

	private:

	};
}

