#include "application.h"

#include "../base/abort.h"

namespace ick{
	Application::Application():
	running_(false){
		
	}
	Application::~Application(){
		if(running_){ ICK_ABORT("has not terminated"); }
	}
	void Application::Launch(){
		if(running_){ ICK_ABORT("already launched"); }
		running_ = true;
	}
	void Application::Terminate(){
		if(!running_){ ICK_ABORT("has not launched"); }
		running_ = false;
	}
}
