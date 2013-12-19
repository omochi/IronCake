//
//  macro.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include "build.h"
#include "std.h"

#define ICK_COMMA ,

#define ICK_ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))

#ifdef ICK_GCC
#	define ICK_FUNC __PRETTY_FUNCTION__
#elif defined ICK_MSVC
#	define ICK_FUNC __FUNCSIG__
#endif

#ifdef ICK_MAC
#	define ICK_PRINTF_LIKE(f,a) __printflike(f,a)
#else
#	define ICK_PRINTF_LIKE(f,a)
#endif