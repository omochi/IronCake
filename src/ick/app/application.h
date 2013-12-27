#pragma once

#include "../base/platform.h"

#ifdef ICK_IOS
#elif defined ICK_MAC && defined __OBJC__
@class NSWindow;
#endif

namespace ick{
	class LoopThread;
	
	class Application {
		bool running_;
		
		LoopThread * master_thread_;
		LoopThread * rendering_thread_;
		
#if defined ICK_MAC && defined __OBJC__
		NSWindow * ns_window_;
		friend void ApplicationSetupNSWindow(Application * thiz);
#endif
	public:
		Application();
		virtual ~Application();
		
#if defined ICK_MAC && defined __OBJC__
		void set_ns_window(NSWindow * ns_window);
#endif
		
		void Launch();
		void Terminate();
	};
}
