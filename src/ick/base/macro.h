//
//  macro.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include "std.h"

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