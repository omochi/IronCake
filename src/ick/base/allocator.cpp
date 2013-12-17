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
#include "crt.h"
#include "log.h"
#include "linked_list.h"

namespace ick{
	Allocator * g_static_allocator = NULL;

	Allocator * static_allocator(){
		return g_static_allocator;
	}
	void set_static_allocator(Allocator * allocator){
		g_static_allocator = allocator;
	}

	void * Allocator::AllocateDebug(size_t size, size_t alignment, const char * format,...){
		(void)format;
		return Allocate(size, alignment);
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
	void MallocAllocator::Free(void * memory){
#ifdef ICK_WINDOWS
		_aligned_free(memory);
#else
		free(memory);
#endif
	}

	const uint32_t DebugAllocator::kHeadSignature = 0xBADDCAFE;
	const uint32_t DebugAllocator::kFootSignature = 0xDEADBEEF;
	
	void * DebugAllocator::BlockGetUserAddress(void * block, size_t alignment){
		return AddressAlign(AddressOffset(block, sizeof(Node *) + sizeof(int32_t)), alignment);
	}
	void DebugAllocator::NodeWriteNodeAddress(Node * node){
		MemoryCopy(&node, AddressOffset(node->value().user, -4-(int)sizeof(Node*)), sizeof(Node*));
	}
	DebugAllocator::Node * DebugAllocator::NodeFromUserAddress(void * user){
		Node * node;
		MemoryCopy(AddressOffset(user, -4-(int)sizeof(Node*)), &node, sizeof(Node*));
		return node;
	}
	uint32_t DebugAllocator::NodeReadHeadSignature(Node * node){
		uint32_t signature;
		MemoryCopy(AddressOffset(node->value().user, -4), &signature, 4);
		return signature;
	}
	void DebugAllocator::NodeWriteHeadSignature(Node * node){
		MemoryCopy(&kHeadSignature, AddressOffset(node->value().user, -4), 4);
	}
	uint32_t DebugAllocator::NodeReadFootSignature(Node * node){
		uint32_t signature;
		MemoryCopy(AddressOffset(node->value().user, (int)node->value().size), &signature, 4);
		return signature;
	}
	void DebugAllocator::NodeWriteFootSignature(Node * node){
		MemoryCopy(&kFootSignature, AddressOffset(node->value().user, (int)node->value().size), 4);
	}
	bool DebugAllocator::NodeCheckSignature(Node * node){
		return
		(NodeReadHeadSignature(node) == kHeadSignature) &&
		(NodeReadFootSignature(node) == kFootSignature);
	}
	
	DebugAllocator::DebugAllocator(Allocator * allocator):
	allocator_(allocator){
		info_list_ = ICK_NEW1_A(allocator, List, allocator);
	}
	DebugAllocator::~DebugAllocator(){
		ICK_DELETE_A(allocator_, info_list_);
	}
	void * DebugAllocator::Allocate(size_t size, size_t alignment){
		return AllocateDebug(size, alignment ,"");
	}
	void * DebugAllocator::AllocateDebug(size_t size, size_t alignment, const char * format,...){
		ICK_ASSERT(alignment > 0);
		
		va_list ap;
		va_start(ap, format);
		char * comment;
		int r = vasprintf(allocator_, &comment, format, ap);
		if(r<0){ ::abort(); }
		va_end(ap);
		
		size_t alloc_size = sizeof(Node *) + 4 + (alignment - 1) + size + 4;
		
		DebugAllocatorBlockInfo info;
		info.block = allocator_->Allocate(alloc_size, alignment);
		info.user = BlockGetUserAddress(info.block, alignment);
		info.size = size;
		info.alignment = alignment;
		info.comment = comment;
		Node * node = info_list_->InsertLast(info);
		
		NodeWriteNodeAddress(node);
		NodeWriteHeadSignature(node);
		NodeWriteFootSignature(node);
				
		return info.user;
	}
	void DebugAllocator::Free(void * memory){
		Node * node = NodeFromUserAddress(memory);
		ICK_FREE_A(allocator_, node->value().comment);
		ICK_FREE_A(allocator_, node->value().block);
		info_list_->Remove(node);
	}
	
	bool DebugAllocator::CheckSignatures(Node ** node){
		for(Node * n = info_list_->first(); n; n = n->next()){
			if(!NodeCheckSignature(n)){
				if(node){ *node = n; }
				return false;
			}
		}
		return true;
	}
	
	void DebugAllocator::Dump(){
		for(Node * node = info_list_->first(); node; node = node->next()){
			ICK_LOG_INFO_A(allocator_,
						   "block: %p, user: %p, size: %zd, alignment: %zd, comment: %s",
						   node->value().block,node->value().user,
						   node->value().size,node->value().alignment,
						   node->value().comment);
		}
	}
	
	DebugAllocator * static_debug_allocator(){
		return static_cast<DebugAllocator *>(g_static_allocator);
	}
}