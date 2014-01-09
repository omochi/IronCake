//
//  build.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/07.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include "platform.h"

#ifndef ICK_DEBUG
#	if defined ICK_ANDROID && ! defined NDEBUG
#		define ICK_DEBUG
#	endif
#endif

#ifndef ICK_DEBUG
#	if defined DEBUG || defined _DEBUG
#		define ICK_DEBUG
#	endif
#endif
