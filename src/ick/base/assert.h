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
#	define ICK_ASSERT(cond) ICK_ASSERT_A(ick::static_allocator(), cond)
#	define ICK_ASSERT_A(allocator, cond) if( ! (cond) ) { ICK_ABORT_A(allocator, "assertion failed (%s) ", #cond); }
#else
#	define ICK_ASSERT(cond)
#	define ICK_ASSERT_A(allocator, cond)
#endif
