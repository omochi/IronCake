//
//  ICKAllocator.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include "macro.h"

namespace ick{
	class Allocator;

	Allocator * static_allocator();
	void set_static_allocator(Allocator * allocator);
	
	class Allocator {
	public:
		virtual ~Allocator(){};
		virtual void * Allocate(size_t size, size_t alignment) = 0;
		virtual void * AllocateDebug(size_t size, size_t alignment, const char * format, ...) ICK_PRINTF_LIKE(4, 5) {
			va_list ap;
			va_start(ap, format);
			void * memory = AllocateDebugV(size, alignment, format, ap);
			va_end(ap);
			return memory;
		}
		virtual void * AllocateDebugV(size_t size, size_t alignment, const char * format, va_list ap) ICK_PRINTF_LIKE(4, 0) = 0;
		virtual void Free(void * memory) = 0;
	};
	
	class MallocAllocator : public Allocator {
	public:
		virtual ~MallocAllocator();
		virtual void * Allocate(size_t size, size_t alignment);
		virtual void * AllocateDebugV(size_t size, size_t alignment, const char * format, va_list ap) ICK_PRINTF_LIKE(4, 0);
		virtual void Free(void * memory);
	};

}
