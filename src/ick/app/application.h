#pragma once

//	Macの場合
//		DisplayLinkでフレームを同期する。
//		遅延する場合は全速で回す。
//		間に合う場合、次の開始をDisplayLinkが来るまで待機する。

#include "application_platform.h"
#include "../thread/mutex.h"

namespace ick{
	class LoopThread;
	class ApplicationController;
	
#ifdef ICK_APP_GLFW
	int ApplicationGLFWMain(int argc, const char * argv [], ApplicationController * (*controller_constructor)() );
#endif
	
	class Application {
	public:
#ifdef ICK_APP_GLFW
		friend int ApplicationGLFWMain(int argc, const char * argv [], ApplicationController * (*controller_constructor)() );
#endif
	private:
		ApplicationController * controller_;
		bool controller_release_;
		
		Mutex running_mutex_;
		bool running_;
		
		LoopThread * master_thread_;
		
		Mutex update_mutex_;
		bool update_running_;
		bool update_deadline_missed_;
		
		LoopThread * render_thread_;
		
		Mutex render_mutex_;
		bool render_running_;
		
#ifdef ICK_APP_GLFW
		bool glfw_do_window_create_;
		GLFWwindow * glfw_window_;
#endif
		
#if defined ICK_MAC && defined __OBJC__
		CVDisplayLinkRef mac_display_link_;
		
		void MacSetupDisplayLink();
		void MacTeardownDisplayLink();
		
		friend CVReturn
		ApplicationMacDisplayLinkOutputCallback(CVDisplayLinkRef displayLink,
												const CVTimeStamp *inNow,
												const CVTimeStamp *inOutputTime,
												CVOptionFlags flagsIn,
												CVOptionFlags *flagsOut,
												void *displayLinkContext);
#endif

#if defined ICK_WINDOWS
		HANDLE win_update_timer_queue_;
		HANDLE win_update_timer_;

		void WinSetupUpdateTimer();
		void WinTeardownUpdateTimer();

		friend VOID NTAPI 
			ApplicationWinUpdateTimerCallback(
				PVOID lpParameter, BOOLEAN TimerOrWaitFired);
#endif

	public:
		Application(ApplicationController * controller, bool controller_release);
		virtual ~Application();
	
		ApplicationController * controller() const;
		
#ifdef ICK_APP_GLFW
		GLFWwindow * glfw_window() const;
#endif
		
		void RequestGLInit();
		void RequestGLRelease();
		
		void Launch();
		void Terminate();
	private:
#ifdef ICK_APP_GLFW
		void GLFWMain();
#endif
		
		//thread: any
		void SignalUpdateTime();
		void RequestUpdate();
		void RequestRender();
		
		//thread: master
		void DoLaunch();
		void DoTerminate();
		void Update();
		
		//thread: render
		void InitRender();
		void Render();

	};
}

