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
#define ICK_NEW0(T) \
	ICK_NEW0_A(g_static_allocator,T)
#define ICK_NEW1(T,a1) \
	ICK_NEW1_A(g_static_allocator,T,a1)
#define ICK_NEW2(T,a1,a2) \
	ICK_NEW2_A(g_static_allocator,T,a1,a2)
#define ICK_NEW3(T,a1,a2,a3) \
	ICK_NEW3_A(g_static_allocator,T,a1,a2,a3)
#define ICK_NEW4(T,a1,a2,a3,a4) \
	ICK_NEW4_A(g_static_allocator,T,a1,a2,a3,a4)
#define ICK_NEW5(T,a1,a2,a3,a4,a5) \
	ICK_NEW5_A(g_static_allocator,T,a1,a2,a3,a4,a5)
#define ICK_NEW6(T,a1,a2,a3,a4,a5,a6) \
	ICK_NEW6_A(g_static_allocator,T,a1,a2,a3,a4,a5,a6)
#define ICK_NEW7(T,a1,a2,a3,a4,a5,a6,a7) \
	ICK_NEW7_A(g_static_allocator,T,a1,a2,a3,a4,a5,a6,a7)
#define ICK_DELETE(obj) ICK_DELETE_A(g_static_allocator,obj)

#ifdef ICK_MEMORY_DEBUG
#	define ICK_ALLOC_A(allocator,T,num) ((T *)(allocator)->AllocateDebug(sizeof(T) * (num),\
		"%s:%s:%d",__FILE__,ICK_FUNC,__LINE__))
#else
#	define ICK_ALLOC_A(allocator,T,num) ((T *)(allocator)->Allocate(sizeof(T) * (num)))
#endif

#define ICK_FREE_A(allocator,memory) (allocator)->Free(memory)
#define ICK_NEW0_A(allocator,T) \
	new ((void *)ICK_ALLOC_A(allocator,T,1)) T()
#define ICK_NEW1_A(allocator,T,a1) \
	new ((void *)ICK_ALLOC_A(allocator,T,1)) T(a1)
#define ICK_NEW2_A(allocator,T,a1,a2) \
	new ((void *)ICK_ALLOC_A(allocator,T,1)) T(a1,a2)
#define ICK_NEW3_A(allocator,T,a1,a2,a3) \
	new ((void *)ICK_ALLOC_A(allocator,T,1)) T(a1,a2,a3)
#define ICK_NEW4_A(allocator,T,a1,a2,a3,a4) \
	new ((void *)ICK_ALLOC_A(allocator,T,1)) T(a1,a2,a3,a4)
#define ICK_NEW5_A(allocator,T,a1,a2,a3,a4,a5) \
	new ((void *)ICK_ALLOC_A(allocator,T,1)) T(a1,a2,a3,a4,a5)
#define ICK_NEW6_A(allocator,T,a1,a2,a3,a4,a5,a6) \
	new ((void *)ICK_ALLOC_A(allocator,T,1)) T(a1,a2,a3,a4,a5,a6)
#define ICK_NEW7_A(allocator,T,a1,a2,a3,a4,a5,a6,a7) \
	new ((void *)ICK_ALLOC_A(allocator,T,1)) T(a1,a2,a3,a4,a5,a6,a7)
#define ICK_DELETE_A(allocator,obj) { ick::Delete(obj); ICK_FREE_A(allocator,obj); }

namespace ick {
	template <typename T> void Delete(T * obj){ obj->~T(); }
}
