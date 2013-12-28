#pragma once

#include "../base/platform.h"

#if ( ! defined ICK_IOS && defined ICK_MAC )
#	define ICK_APP_GLFW
#endif

#ifdef ICK_APP_GLFW
#	include <GLFW/glfw3.h>
#endif

#ifdef ICK_IOS
#elif defined ICK_MAC && defined __OBJC__
#	import <AppKit/AppKit.h>
#	import <CoreVideo/CoreVideo.h>
#endif

