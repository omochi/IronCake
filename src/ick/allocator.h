//
//  ICKAllocator.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include <stdlib.h>

namespace ick{
	class Allocator {
	public:
		virtual ~Allocator();
		virtual void * Allocate(size_t size) = 0;
		virtual void * AllocateDebug(size_t size,const char * format,...);
		virtual void Free(void * memory) = 0;
	};
	
	extern Allocator * g_static_allocator;
	
	class MallocAllocator : public Allocator {
	public:
		virtual ~MallocAllocator();
		virtual void * Allocate(size_t size);
		virtual void Free(void * memory);
	};
	
	class DebugAllocator : public Allocator {
		Allocator * allocator;
	public:
		DebugAllocator(Allocator * allocator);
		virtual ~DebugAllocator();
		virtual void * Allocate(size_t size);
		virtual void * AllocateDebug(size_t size,const char * format,...);
		virtual void Free(void * memory);
	};
}
