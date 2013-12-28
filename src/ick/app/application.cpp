#include "application.h"

#include "../base/memory.h"
#include "../base/abort.h"
#include "../base/time.h"
#include "../function/function.h"
#include "../thread/scoped_lock.h"
#include "../thread/loop_thread.h"

#include "application_controller.h"

#ifdef ICK_OBJCPP_GUARD

namespace ick{
	Application::Application(ApplicationController * controller):
	controller_(controller),
	running_(false)
	{
		ICK_ASSERT(controller);
		glfw_window_ = NULL;
		
		master_thread_ = ICK_NEW(LoopThread);
		master_thread_->Start();
	}
	
	Application::~Application(){
		if(running_){ ICK_ABORT("has not terminated"); }
		
		master_thread_->PostQuit();
		master_thread_->Join();
		ICK_DELETE(master_thread_);
	}
	
	ApplicationController * Application::controller() const{
		return controller_;
	}
		
#ifdef ICK_APP_GLFW

	GLFWwindow * Application::glfw_window() const{
		return glfw_window_;
	}
	
	void Application::set_glfw_window(GLFWwindow *glfw_window){
		glfw_window_ = glfw_window;
	}

#endif
	
	void Application::Launch(){
		master_thread_->Post(FunctionMake(this, &Application::DoLaunch));
#ifdef ICK_MAC
		MacSetupDisplayLink();
#endif
		
		running_mutex_.Lock();
		while(!running_){ running_mutex_.Wait(); }
		running_mutex_.Unlock();
	}
	void Application::Terminate(){
#ifdef ICK_MAC
		MacTeardownDisplayLink();
#endif
		master_thread_->Post(FunctionMake(this, &Application::DoTerminate));
		
		running_mutex_.Lock();
		while(running_){ running_mutex_.Wait(); }
		running_mutex_.Unlock();
	}
	
	void Application::DoLaunch(){
		if(running_){ ICK_ABORT("already launched"); }
		update_running_ = false;
		update_deadline_missed_ = false;
		
		rendering_thread_ = ICK_NEW(LoopThread);
		rendering_thread_->Start();
		
		running_mutex_.Lock();
		running_ = true;
		running_mutex_.Broadcast();
		running_mutex_.Unlock();
		
		controller_->ApplicationDidLaunch(this);
	}
	
	void Application::DoTerminate(){
		if(!running_){ ICK_ABORT("has not launched"); }
		
		controller_->ApplicationWillTerminate(this);
		
		rendering_thread_->PostQuit();
		rendering_thread_->Join();
		ICK_DELETE(rendering_thread_);
		
		running_mutex_.Lock();
		running_ = false;
		running_mutex_.Broadcast();
		running_mutex_.Unlock();
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
		
		controller_->ApplicationOnUpdate(this);
		
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
