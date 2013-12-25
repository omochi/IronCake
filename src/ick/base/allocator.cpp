//
//  ICKAllocator.cpp
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "allocator.h"

#ifdef ICK_WINDOWS
#	include <malloc.h>
#endif

#include "memory.h"

namespace ick{
	Allocator * g_static_allocator = NULL;

	Allocator * static_allocator(){
		return g_static_allocator;
	}
	void set_static_allocator(Allocator * allocator){
		g_static_allocator = allocator;
	}

	MallocAllocator::~MallocAllocator(){
		
	}
	void * MallocAllocator::Allocate(size_t size, size_t alignment){
#ifdef ICK_WINDOWS
		return _aligned_malloc(size, alignment);
#else
		void * memory;
		if(alignment < sizeof(void *)){ alignment = sizeof(void *); }
		if (posix_memalign(&memory, alignment, size)){ abort(); }
		return memory;
#endif
	}
	
	void * MallocAllocator::AllocateDebugV(size_t size, size_t alignment, const char * format, va_list ap){
		(void)format;
		(void)ap;
		return Allocate(size, alignment);
	}
	
	void MallocAllocator::Free(void * memory){
#ifdef ICK_WINDOWS
		_aligned_free(memory);
#else
		free(memory);
#endif
	}

}