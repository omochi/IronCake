#include "application.cpp"

namespace ick{

	void ApplicationSetupNSWindow(Application * thiz){
		NSScreen * screen = [thiz->ns_window_ screen];
		NSDictionary * desc = [screen deviceDescription];
		CGDirectDisplayID displayId = static_cast<CGDirectDisplayID>([desc[@"NSScreenNumber"] intValue]);
		
	}
	
}