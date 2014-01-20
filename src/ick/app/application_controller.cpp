#include "application_controller.h"

namespace ick{

	ApplicationController::~ApplicationController(){}
	Application * ApplicationController::application() const{
		return application_;
	}
	void ApplicationController::DidLaunch(){
	}
	void ApplicationController::WillTerminate(){
	}
	void ApplicationController::DidInitGL(){
	}
	void ApplicationController::WillReleaseGL(){
	}
	void ApplicationController::OnUpdate(){
	}
	void ApplicationController::OnRender(){
	}
	
}
