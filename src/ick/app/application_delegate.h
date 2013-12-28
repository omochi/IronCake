#pragma once

//	ユーザコンテンツのつなぎ込みのルート

namespace ick{
	class ApplicationDelegate {
	public:
		virtual ~ApplicationDeleagte(){}
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
