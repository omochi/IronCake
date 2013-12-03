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
#	endif
#	ifdef TARGET_OS_MAC
#		define ICK_MAC
#	endif
#endif

