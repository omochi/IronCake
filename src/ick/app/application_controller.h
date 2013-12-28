#pragma once

//	ユーザコンテンツのつなぎ込みのルート

namespace ick{
	class Application;
	
	class ApplicationController {
		friend Application;
		Application * application_;
	public:
		virtual ~ApplicationController();
		//thread: master
		virtual void ApplicationDidLaunch();
		virtual void ApplicationWillTerminate();
		virtual void ApplicationOnUpdate();
		//thread: render
		virtual void ApplicationOnRender();
	};
	
}
