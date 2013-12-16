//
//  compiler.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#ifdef __GNUC__
#	define ICK_GCC
#elif defined _MSC_VER
#	define ICK_MSVC
#endif

#ifdef ICK_GCC
#	define ICK_NO_EMPTY_DUMMY
#endif

#ifdef ICK_MSVC
#	define ICK_NO_EMPTY_DUMMY namespace { char dummy; };
#endif

