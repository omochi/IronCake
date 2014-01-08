//
//  compiler.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#ifdef __clang__
#	define ICK_CLANG
#endif
#ifdef __GNUC__
#	define ICK_GCC
#endif
#ifdef _MSC_VER
#	define ICK_MSVC
#endif

#ifdef ICK_CLANG
#	define ICK_PRINTF_LIKE(f,a) __attribute__((__format__ (__printf__, f, a)))
#elif ICK_GCC
#	define ICK_PRINTF_LIKE(f,a) __attribute__((format(printf, f, a)))
#else
#	define ICK_PRINTF_LIKE(f,a)
#endif

#ifdef ICK_MSVC
#	define ICK_NO_EMPTY_DUMMY namespace { char dummy; };
#else
#	define ICK_NO_EMPTY_DUMMY
#endif

#ifdef ICK_GCC
#	define ICK_FUNC __PRETTY_FUNCTION__
#	define ICK_PRI_SIZE_T "%zd"
#elif defined ICK_MSVC
#	define ICK_FUNC __FUNCSIG__
#	define ICK_PRI_SIZE_T "%Iu"
#endif
