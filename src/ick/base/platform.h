//
//  ICKEnv.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#ifdef __APPLE__
#	include <TargetConditionals.h>
#	if TARGET_OS_IPHONE
#		define ICK_IOS
#	endif
#	if TARGET_OS_MAC
#		define ICK_MAC
#	endif
#endif

#ifdef _WIN32
#	define ICK_WINDOWS
#endif

#ifdef __linux
#	define ICK_LINUX
#endif

#ifdef __ANDROID__
#	define ICK_ANDROID
#endif

#if ( ! defined ICK_MAC ) || ( defined __OBJC__ )
#	define ICK_OBJCPP_GUARD
#endif