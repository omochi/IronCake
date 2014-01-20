#pragma once

//	ユーザコンテンツのつなぎ込みのルート

namespace ick{
	class Application;
	
	class ApplicationController {
		friend Application;
		Application * application_;
	public:
		virtual ~ApplicationController();
		
		Application * application() const;
		
		virtual void DidLaunch();
		virtual void WillTerminate();
		
		virtual void DidInitGL();
		virtual void WillReleaseGL();
		
		virtual void OnUpdate();
		virtual void OnRender();
	};
	
}
