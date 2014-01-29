#include "application.cpp"

#ifdef ICK_APP_GLFW
#	ifdef ICK_MAC
#		define GLFW_EXPOSE_NATIVE_COCOA
#		define GLFW_EXPOSE_NATIVE_NSGL
#	endif
#	include <GLFW/glfw3native.h>
#endif

namespace ick{
		

	
}