//
//  assert.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/04.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include "abort.h"

#ifdef ICK_DEBUG
#define ICK_ASSERT(cond, format, ...) if( ! (cond) ) { ICK_ABORT(format, ##__VA_ARGS__); }
#else
#define ICK_ASSERT(cond, format, ...)
#endif
