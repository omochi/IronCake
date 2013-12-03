//
//  memory.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include <new>

#include "macro.h"
#include "allocator.h"

#define ICK_ALLOC(T,num) ICK_ALLOC_A(g_static_allocator,T,num)
#define ICK_FREE(memory) ICK_FREE_A(g_static_allocator,memory)
#define ICK_NEW(T,...) ICK_NEW_A(g_static_allocator,T,##__VA_ARGS__)
#define ICK_DELETE(obj) ICK_DELETE_A(g_static_allocator,obj)

#ifdef ICK_MEMORY_DEBUG
#	define ICK_ALLOC_A(allocator,T,num) ((T *)(allocator)->AllocateDebug(sizeof(T) * (num),\
		"%s:%s:%d",__FILE__,ICK_FUNC,__LINE__))
#else
#	define ICK_ALLOC_A(allocator,T,num) ((T *)(allocator)->Allocate(sizeof(T) * (num)))
#endif

#define ICK_FREE_A(allocator,memory) (allocator)->Free(memory)
#define ICK_NEW_A(allocator,T,...) (new ((void *) ICK_ALLOC_A(allocator,T,1) ) T(__VA_ARGS__) )
#define ICK_DELETE_A(allocator,obj) { ick::Delete(obj); ICK_FREE_A(allocator,obj); }

namespace ick {
	template <typename T> void Delete(T * obj){ obj->~T(); }
}
