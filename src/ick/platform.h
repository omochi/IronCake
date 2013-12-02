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
#	ifdef TARGET_OS_IPHONE
#		define ICK_IOS
#	elif defined TARGET_OS_MAC
#		define ICK_OSX
#	endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
