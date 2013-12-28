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

#ifndef ICK_MEMORY_DEBUG
#	define ICK_MEMORY_COMMENT_ARGS
#	define ICK_FUNC_ALLOC ick::Alloc
#	define ICK_FUNC_ALLOC_A ick::AllocA
#else
#	define ICK_MEMORY_COMMENT_ARGS ,"%s:%s:%d",__FILE__,ICK_FUNC,__LINE__
#	define ICK_FUNC_ALLOC ick::AllocDebug
#	define ICK_FUNC_ALLOC_A ick::AllocDebugA
#endif

#define ICK_ALLOC(T,num) ICK_FUNC_ALLOC<T,T>(num ICK_MEMORY_COMMENT_ARGS)
#define ICK_ALLOC_A(allocator,T,num) ICK_FUNC_ALLOC_A<T,T>(allocator,num ICK_MEMORY_COMMENT_ARGS)
#define ICK_NEW(T,...) new (ICK_FUNC_ALLOC<void, T>(1 ICK_MEMORY_COMMENT_ARGS)) T(__VA_ARGS__)
#define ICK_NEW_A(allocator,T,...) new (ICK_FUNC_ALLOC_A<void, T>(allocator,1 ICK_MEMORY_COMMENT_ARGS)) T(__VA_ARGS__)

#define ICK_FREE(memory) ick::static_allocator()->Free(memory)
#define ICK_FREE_A(allocator, memory) (allocator)->Free(memory)
#define ICK_DELETE(obj) { ick::Destroy(obj); ick::static_allocator()->Free(obj); }
#define ICK_DELETE_A(allocator,obj) { ick::Destroy(obj); (allocator)->Free(obj); }

namespace ick {
	template <typename T> size_t AlignmentOf();

	template <typename R, typename T> R * Alloc(int num);
	template <typename R, typename T> R * AllocA(Allocator * allocator, int num);
	
	template <typename R, typename T> R * AllocDebug(int num, const char * format, ...);
	template <typename R, typename T> R * AllocDebugV(int num, const char * format, va_list ap);
	template <typename R, typename T> R * AllocDebugA(Allocator * allocator, int num, const char * format, ...);
	template <typename R, typename T> R * AllocDebugAV(Allocator * allocator, int num, const char * format, va_list ap);
	
	template <typename T> void Destroy(T * obj);
	
	void * AddressOffset(void * address, int offset);
	void * AddressAlign(void * address, size_t alignment);
	void MemoryCopy(const void * src, void * dest, size_t size);
	
	template <typename T> class AlignmentOf_ {
		struct helper {
			char a_;
			T b_;
		};
	public:
		static const size_t value = offsetof(struct helper, b_);
	};
	
	template <typename T> size_t AlignmentOf() { return AlignmentOf_<T>::value; }

	template <typename R, typename T> R * Alloc(int num){
		return AllocA<R, T>(static_allocator(), num);
	}
	template <typename R, typename T> R * AllocA(Allocator * allocator, int num){
		return static_cast<R *>(allocator->Allocate(sizeof(T) * static_cast<size_t>(num), AlignmentOf<T>()));
	}
	template <typename R, typename T> R * AllocDebug(int num, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		R * memory = AllocDebugV<R,T>(num, format, ap);
		va_end(ap);
		return memory;
	}
	template <typename R, typename T> R * AllocDebugV(int num, const char * format, va_list ap){
		return AllocDebugAV<R,T>(static_allocator(), num, format, ap);
	}
	template <typename R, typename T> R * AllocDebugA(Allocator * allocator, int num, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		R * memory = AllocDebugAV<R, T>(allocator, num, format, ap);
		va_end(ap);
		return memory;
	}
	template <typename R, typename T> R * AllocDebugAV(Allocator * allocator, int num, const char * format, va_list ap){
		return static_cast<R *>(allocator->AllocateDebugV(sizeof(T) * static_cast<size_t>(num), AlignmentOf<T>(), format, ap));
	}
	template <typename T> void Destroy(T * obj){ obj->~T(); }
}
