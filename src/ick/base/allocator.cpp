//
//  ICKAllocator.cpp
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "allocator.h"

#include <stdlib.h>

namespace ick{
	Allocator::~Allocator(){
	}
	void * Allocator::AllocateDebug(size_t size,const char * format,...){
		return Allocate(size);
	}
	
	Allocator * g_static_allocator = NULL;
	
	MallocAllocator::~MallocAllocator(){
		
	}
	void * MallocAllocator::Allocate(size_t size){
		return malloc(size);
	}
	void MallocAllocator::Free(void * memory){
		free(memory);
	}
	
	DebugAllocator::DebugAllocator(Allocator * allocator):
	allocator(allocator){
		
	}
	DebugAllocator::~DebugAllocator(){
		
	}
	void * DebugAllocator::Allocate(size_t size){
		return AllocateDebug(size,"");
	}
	void * DebugAllocator::AllocateDebug(size_t size,const char * format,...){
		return NULL;
	}
	void DebugAllocator::Free(void * memory){
		
	}
}