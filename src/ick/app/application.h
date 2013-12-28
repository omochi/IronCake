#pragma once

//	Macの場合
//		DisplayLinkでフレームを同期する。
//		遅延する場合は全速で回す。
//		間に合う場合、次の開始をDisplayLinkが来るまで待機する。

#include "../base/platform.h"
#include "../thread/mutex.h"

#ifdef ICK_IOS
#elif defined ICK_MAC && defined __OBJC__
#	import <AppKit/AppKit.h>
#	import <CoreVideo/CoreVideo.h>
#endif

#if ( ! defined ICK_IOS && defined ICK_MAC )
#	define ICK_APP_GLFW
#endif

#ifdef ICK_APP_GLFW
#	include <GLFW/glfw3.h>
#endif

namespace ick{
	class LoopThread;
	class ApplicationDelegate;
	
	class Application {
		ApplicationDelegate * delegate_;
		
		Mutex running_mutex_;
		bool running_;
		
		LoopThread * master_thread_;
		LoopThread * rendering_thread_;
		
		Mutex update_mutex_;
		bool update_running_;
		bool update_deadline_missed_;
		
#ifdef ICK_APP_GLFW
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
	public:
		Application();
		virtual ~Application();
	
		//thread: main
		ApplicationDelegate * delegate() const;
		void set_delegate(ApplicationDelegate * delagete);
		
#ifdef ICK_APP_GLFW
		//thread: main
		GLFWwindow * glfw_window() const;
		void set_glfw_window(GLFWwindow * glfw_window);
#endif
		
		//thread: main
		void Launch();
		void Terminate();

	private:
		void DoLaunch();
		void DoTerminate();
		
		//thread: any
		void SignalUpdateTime();
		
		//thread: any, UpdateをマスタースレッドにPostする
		void PostUpdate();
		
		void Update();
		void UpdateEnd();
	};
}
