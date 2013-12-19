﻿//
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

#ifdef ICK_MEMORY_DEBUG
#	define ICK_ALLOC(T,num) ick::AllocDebug<T>(num,"%s:%s:%d",__FILE__,ICK_FUNC,__LINE__)
#	define ICK_ALLOC_A(allocator,T,num) ick::AllocDebugA<T>(allocator,num,"%s:%s:%d",__FILE__,ICK_FUNC,__LINE__)
#	define ICK_NEW(T,...) new (static_cast<void *>(ick::AllocDebug<T>(1,"%s:%s:%d",__FILE__,ICK_FUNC,__LINE__))) T(__VA_ARGS__)
#	define ICK_NEW_A(allocator,T,...) new (static_cast<void *>(ick::AllocDebugA<T>(allocator,1,"%s:%s:%d",__FILE__,ICK_FUNC,__LINE__))) T(__VA_ARGS__)
#else
#	define ICK_ALLOC(T,num) ick::Alloc<T>(num)
#	define ICK_ALLOC_A(allocator,T,num) ick::AllocA<T>(allocator,num)
#	define ICK_NEW(T,...) new (static_cast<void *>(ick::Alloc<T>(1,"%s:%s:%d",__FILE__,ICK_FUNC,__LINE__))) T(__VA_ARGS__)
#	define ICK_NEW_A(allocator,T,...) new (static_cast<void *>(ick::AllocDebug<T>(allocator,1,"%s:%s:%d",__FILE__,ICK_FUNC,__LINE__))) T(__VA_ARGS__)
#endif

#define ICK_FREE(memory) ick::static_allocator()->Free(memory)
#define ICK_FREE_A(allocator, memory) (allocator)->Free(memory)
#define ICK_DELETE(obj) { ick::Destroy(obj); ick::static_allocator()->Free(obj); }
#define ICK_DELETE_A(allocator,obj) { ick::Destroy(obj); (allocator)->Free(obj); }

//#define ICK_ALLOC(T,num) ICK_ALLOC_A(ick::static_allocator(),T,num)
//#define ICK_FREE(memory) ICK_FREE_A(ick::static_allocator(),memory)
//
//#define ICK_NEW0(T) \
//	ICK_NEW0_A(ick::static_allocator(),T)
//#define ICK_NEW1(T,a1) \
//	ICK_NEW1_A(ick::static_allocator(),T,a1)
//#define ICK_NEW2(T,a1,a2) \
//	ICK_NEW2_A(ick::static_allocator(),T,a1,a2)
//#define ICK_NEW3(T,a1,a2,a3) \
//	ICK_NEW3_A(ick::static_allocator(),T,a1,a2,a3)
//#define ICK_NEW4(T,a1,a2,a3,a4) \
//	ICK_NEW4_A(ick::static_allocator(),T,a1,a2,a3,a4)
//#define ICK_NEW5(T,a1,a2,a3,a4,a5) \
//	ICK_NEW5_A(ick::static_allocator(),T,a1,a2,a3,a4,a5)
//#define ICK_NEW6(T,a1,a2,a3,a4,a5,a6) \
//	ICK_NEW6_A(ick::static_allocator(),T,a1,a2,a3,a4,a5,a6)
//#define ICK_NEW7(T,a1,a2,a3,a4,a5,a6,a7) \
//	ICK_NEW7_A(ick::static_allocator(),T,a1,a2,a3,a4,a5,a6,a7)
//#define ICK_DELETE(obj) ICK_DELETE_A(ick::static_allocator(), obj)
//
//#ifdef ICK_MEMORY_DEBUG
//#	define ICK_ALLOC_A(allocator,T,num) ((T *)(allocator)->AllocateDebug(\
//		sizeof(T) * static_cast<size_t>(num),ick::AlignmentOf<T>(),\
//		"%s:%s:%d",__FILE__,ICK_FUNC,__LINE__))
//#else
//#	define ICK_ALLOC_A(allocator,T,num) ((T *)(allocator)->Allocate(\
//		sizeof(T) * static_cast<size_t>(num),ick::AlignmentOf<T>()))
//#endif
//
//#define ICK_FREE_A(allocator,memory) (allocator)->Free(memory)
//#define ICK_NEW0_A(allocator,T) \
//	new ((void *)ICK_ALLOC_A(allocator,T,1)) T()
//#define ICK_NEW1_A(allocator,T,a1) \
//	new ((void *)ICK_ALLOC_A(allocator,T,1)) T(a1)
//#define ICK_NEW2_A(allocator,T,a1,a2) \
//	new ((void *)ICK_ALLOC_A(allocator,T,1)) T(a1,a2)
//#define ICK_NEW3_A(allocator,T,a1,a2,a3) \
//	new ((void *)ICK_ALLOC_A(allocator,T,1)) T(a1,a2,a3)
//#define ICK_NEW4_A(allocator,T,a1,a2,a3,a4) \
//	new ((void *)ICK_ALLOC_A(allocator,T,1)) T(a1,a2,a3,a4)
//#define ICK_NEW5_A(allocator,T,a1,a2,a3,a4,a5) \
//	new ((void *)ICK_ALLOC_A(allocator,T,1)) T(a1,a2,a3,a4,a5)
//#define ICK_NEW6_A(allocator,T,a1,a2,a3,a4,a5,a6) \
//	new ((void *)ICK_ALLOC_A(allocator,T,1)) T(a1,a2,a3,a4,a5,a6)
//#define ICK_NEW7_A(allocator,T,a1,a2,a3,a4,a5,a6,a7) \
//	new ((void *)ICK_ALLOC_A(allocator,T,1)) T(a1,a2,a3,a4,a5,a6,a7)
//#define ICK_DELETE_A(allocator,obj) { ick::Destroy(obj); ICK_FREE_A(allocator, obj); }

namespace ick {
	template <typename T> size_t AlignmentOf();

	template <typename T> T * Alloc(int num);
	template <typename T> T * AllocA(Allocator * allocator, int num);
	
	template <typename T> T * AllocDebug(int num, const char * format, ...);
	template <typename T> T * AllocDebugV(int num, const char * format, va_list ap);
	template <typename T> T * AllocDebugA(Allocator * allocator, int num, const char * format, ...);
	template <typename T> T * AllocDebugAV(Allocator * allocator, int num, const char * format, va_list ap);
	
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

	template <typename T> T * Alloc(int num){
		return AllocA<T>(static_allocator(), num);
	}
	template <typename T> T * AllocA(Allocator * allocator, int num){
		return allocator->Allocate(sizeof(T) * static_cast<size_t>(num), AlignmentOf<T>());
	}
	template <typename T> T * AllocDebug(int num, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		T * memory = AllocDebugV<T>(num, format, ap);
		va_end(ap);
	}
	template <typename T> T * AllocDebugV(int num, const char * format, va_list ap){
		return AllocDebugAV<T>(static_allocator(), num, format, ap);
	}
	template <typename T> T * AllocDebugA(Allocator * allocator, int num, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		T * memory = AllocDebugAV<T>(allocator, num, format, ap);
		va_end(ap);
	}
	template <typename T> T * AllocDebugAV(Allocator * allocator, int num, const char * format, va_list ap){
		return allocator->AllocateDebug(sizeof(T) * static_cast<size_t>(num), AlignmentOf<T>(), format, ap);
	}
	template <typename T> void Destroy(T * obj){ obj->~T(); }
}
