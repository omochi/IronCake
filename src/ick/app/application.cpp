#include "application.h"

#include "../base/memory.h"
#include "../base/abort.h"
#include "../thread/loop_thread.h"

#ifdef ICK_IOS
#elif defined ICK_MAC
#	ifdef __OBJC__
#		import <AppKit/AppKit.h>
#	endif
#endif

#ifdef ICK_OBJCPP_GUARD

namespace ick{
	Application::Application():
	running_(false){
		
	}
	Application::~Application(){
		if(running_){ ICK_ABORT("has not terminated"); }
	}
	
#ifdef ICK_MAC
	void Application::set_ns_window(NSWindow *ns_window){
		ns_window_ = ns_window;
	}
#endif
	
	void Application::Launch(){
		if(running_){ ICK_ABORT("already launched"); }
		running_ = true;
		
		master_thread_ = ICK_NEW(LoopThread);
		master_thread_->Start();
		
		rendering_thread_ = ICK_NEW(LoopThread);
		rendering_thread_->Start();
		
#ifdef ICK_MAC
		ApplicationSetupNSWindow(this);
#endif
	}
	void Application::Terminate(){
		if(!running_){ ICK_ABORT("has not launched"); }
		running_ = false;
		
		
		master_thread_->PostQuit();
		master_thread_->Join();
		ICK_DELETE(master_thread_);
		
		rendering_thread_->PostQuit();
		rendering_thread_->Join();
		ICK_DELETE(rendering_thread_);
	}
}

#endif
