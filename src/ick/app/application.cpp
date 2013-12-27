#include "application.h"

#include "../base/memory.h"
#include "../base/abort.h"
#include "../function/function.h"
#include "../thread/scoped_lock.h"
#include "../thread/loop_thread.h"

#ifdef ICK_OBJCPP_GUARD

namespace ick{
	Application::Application():
	running_(false){
		
	}
	Application::~Application(){
		if(running_){ ICK_ABORT("has not terminated"); }
	}
	
#ifdef ICK_MAC

#endif
	
	void Application::Launch(){
		if(running_){ ICK_ABORT("already launched"); }
		running_ = true;
		
		update_running_ = false;
		update_deadline_missed_ = false;
		
		master_thread_ = ICK_NEW(LoopThread);
		master_thread_->Start();
		
		rendering_thread_ = ICK_NEW(LoopThread);
		rendering_thread_->Start();
		
#ifdef ICK_MAC
		MacSetupDisplayLink();
#endif
	}
	void Application::Terminate(){
		if(!running_){ ICK_ABORT("has not launched"); }
		running_ = false;
		
#ifdef ICK_MAC
		MacTeardownDisplayLink();
		mac_window_ = nil;
#endif
		
		master_thread_->PostQuit();
		master_thread_->Join();
		ICK_DELETE(master_thread_);
		
		rendering_thread_->PostQuit();
		rendering_thread_->Join();
		ICK_DELETE(rendering_thread_);
	}
	
	void Application::SignalUpdateTime(){
		ICK_SCOPED_LOCK(update_mutex_);
		
		if(update_running_){
			update_deadline_missed_ = true;
		}else{
			PostUpdate();
		}
	}
	
	void Application::PostUpdate(){
		ICK_SCOPED_LOCK(update_mutex_);
		update_running_ = true;
		update_deadline_missed_ = false;
		
		master_thread_->Post(FunctionMake(this, &Application::Update));
	}
	
	void Application::Update(){
		
		UpdateEnd();
	}
	
	void Application::UpdateEnd(){
		ICK_SCOPED_LOCK(update_mutex_);
		if(update_deadline_missed_){
			PostUpdate();
		}else{
			update_running_ = false;
		}
	}
	
}

#endif
