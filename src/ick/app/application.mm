#include "application.cpp"

namespace ick{
	
	CVReturn ApplicationMacDisplayLinkOutputCallback(CVDisplayLinkRef displayLink,
													 const CVTimeStamp *inNow,
													 const CVTimeStamp *inOutputTime,
													 CVOptionFlags flagsIn,
													 CVOptionFlags *flagsOut,
													 void *displayLinkContext){
		Application * thiz = static_cast<Application *>(displayLinkContext);
		
	}
	
	void Application::set_mac_window(NSWindow *mac_window){
		mac_window_ = mac_window;
	}
	void Application::MacSetupDisplayLink(){
		NSScreen * screen = [mac_window_ screen];
		NSDictionary * desc = [screen deviceDescription];
		CGDirectDisplayID displayId = static_cast<CGDirectDisplayID>([desc[@"NSScreenNumber"] intValue]);
		CVReturn ret = CVDisplayLinkCreateWithCGDisplay(displayId, &mac_display_link_);
		if(ret){ ICK_ABORT("CVDisplayLinkCreateWithCGDisplay"); }
		CVDisplayLinkSetOutputCallback(mac_display_link_,
									   & ApplicationMacDisplayLinkOutputCallback,
									   this);
		CVDisplayLinkStart(mac_display_link_);
	}
	
	void Application::MacTeardownDisplayLink(){
		CVDisplayLinkStop(mac_display_link_);
		CVDisplayLinkRelease(mac_display_link_);
		mac_display_link_ = NULL;
	}
	

	
}