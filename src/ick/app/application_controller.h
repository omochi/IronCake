#pragma once

//	ユーザコンテンツのつなぎ込みのルート

namespace ick{
	class Application;
	
	class ApplicationController {
	public:
		virtual ~ApplicationController(){}
		virtual void ApplicationDidLaunch(Application * application){
			(void)application;
		}
		virtual void ApplicationWillTerminate(Application * application){
			(void)application;
		}
		virtual void ApplicationOnUpdate(Application * application){
			(void)application;
		}
	};
	
}
