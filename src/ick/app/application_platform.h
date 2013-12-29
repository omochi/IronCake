#pragma once

#include "../base/platform.h"

#ifdef ICK_IOS
#elif defined ICK_MAC && defined __OBJC__
#	import <AppKit/AppKit.h>
#	import <CoreVideo/CoreVideo.h>
#endif

#ifdef ICK_WINDOWS
#	include <Windows.h>
#endif

#if ( ! defined ICK_IOS && defined ICK_MAC ) || \
	(defined ICK_WINDOWS)
#	define ICK_APP_GLFW
#endif

#ifdef ICK_APP_GLFW
#	include <GLFW/glfw3.h>
#endif