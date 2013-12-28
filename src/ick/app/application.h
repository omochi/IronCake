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

namespace ick{
	class LoopThread;
	
	class ApplicationDelegate;
	
	class Application {
		bool running_;
		
		LoopThread * master_thread_;
		LoopThread * rendering_thread_;
		
		Mutex update_mutex_;
		bool update_running_;
		bool update_deadline_missed_;
				
#if defined ICK_MAC && defined __OBJC__
		NSWindow * mac_window_;
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
		
#if defined ICK_MAC && defined __OBJC__
		//thread: main
		void set_mac_window(NSWindow * mac_window);
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
