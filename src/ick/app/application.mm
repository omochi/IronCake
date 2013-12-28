#include "application.cpp"

#ifdef ICK_APP_GLFW
#	ifdef ICK_MAC
#		define GLFW_EXPOSE_NATIVE_COCOA
#		define GLFW_EXPOSE_NATIVE_NSGL
#	endif
#	include <GLFW/glfw3native.h>
#endif

namespace ick{
	
	CVReturn ApplicationMacDisplayLinkOutputCallback(CVDisplayLinkRef displayLink,
													 const CVTimeStamp *inNow,
													 const CVTimeStamp *inOutputTime,
													 CVOptionFlags flagsIn,
													 CVOptionFlags *flagsOut,
													 void *displayLinkContext){
		(void)displayLink;
		(void)inNow;
		(void)inOutputTime;
		(void)flagsIn;
		(void)flagsOut;
		Application * thiz = static_cast<Application *>(displayLinkContext);
		thiz->SignalUpdateTime();
		return kCVReturnSuccess;
	}

	void Application::MacSetupDisplayLink(){
		NSWindow * mac_window = glfwGetCocoaWindow(glfw_window_);
		NSScreen * screen = [mac_window screen];
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