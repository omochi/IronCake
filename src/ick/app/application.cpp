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
		controller_->application_ = this;
		
		glfw_window_ = NULL;
		
		master_thread_ = ICK_NEW(LoopThread);
		master_thread_->set_name(String("master"));
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
		{
			ICK_SCOPED_LOCK(running_mutex_);
			while(!running_){ running_mutex_.Wait(); }
		}
	}
	void Application::Terminate(){
		master_thread_->Post(FunctionMake(this, &Application::DoTerminate));
		{
			ICK_SCOPED_LOCK(running_mutex_);
			while(running_){ running_mutex_.Wait(); }
		}
	}
	
	void Application::SignalUpdateTime(){
		ICK_SCOPED_LOCK(update_mutex_);
		
		if(update_running_){
			update_deadline_missed_ = true;
		}else{
			RequestUpdate();
		}
	}
	
	void Application::RequestUpdate(){
		ICK_SCOPED_LOCK(update_mutex_);
		update_running_ = true;
		update_deadline_missed_ = false;
		
		master_thread_->Post(FunctionMake(this, &Application::Update));
	}
	
	void Application::RequestRender(){
		ICK_SCOPED_LOCK(render_mutex_);
		render_running_ = true;
	
		render_thread_->Post(FunctionMake(this, &Application::Render));
	}
	
	void Application::DoLaunch(){
		if(running_){ ICK_ABORT("already launched"); }
		update_running_ = false;
		update_deadline_missed_ = false;
		render_running_ = false;
		
		render_thread_ = ICK_NEW(LoopThread);
		render_thread_->set_name(String("render"));
		render_thread_->Start();
		render_thread_->Post(FunctionMake(this, &Application::InitRender));
		
#ifdef ICK_MAC
		MacSetupDisplayLink();
#endif
		
		{
			ICK_SCOPED_LOCK(running_mutex_);
			running_ = true;
			running_mutex_.Broadcast();
		}
		
		controller_->ApplicationDidLaunch();
	}
	
	void Application::DoTerminate(){
		if(!running_){ ICK_ABORT("has not launched"); }
		
		controller_->ApplicationWillTerminate();
		
#ifdef ICK_MAC
		MacTeardownDisplayLink();
#endif
		
		render_thread_->PostQuit();
		render_thread_->Join();
		ICK_DELETE(render_thread_);
		
		{
			ICK_SCOPED_LOCK(running_mutex_);
			running_ = false;
			running_mutex_.Broadcast();
		}
	}
	
	void Application::Update(){
		{
			ICK_SCOPED_LOCK(running_mutex_);
			if(!running_){ return; }
		}
		
		controller_->ApplicationOnUpdate();
		
		{
			ICK_SCOPED_LOCK(render_mutex_);
			RequestRender();
			while(render_running_){ render_mutex_.Wait(); }
		}

		{
			ICK_SCOPED_LOCK(update_mutex_);
			if(update_deadline_missed_){
				RequestUpdate();
			}else{
				update_running_ = false;
			}
		}
	}
	
	void Application::InitRender(){
#ifdef ICK_APP_GLFW
		glfwSwapInterval(0);
		glfwMakeContextCurrent(glfw_window_);
#endif
	}
	
	void Application::Render(){
		controller_->ApplicationOnRender();
		
#ifdef ICK_APP_GLFW
		glfwSwapBuffers(glfw_window_);
#endif
		{
			ICK_SCOPED_LOCK(render_mutex_);
			render_running_ = false;
			render_mutex_.Broadcast();
		}
	}
	
}

#endif
