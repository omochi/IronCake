//
//  ICKAllocator.cpp
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "allocator.h"

#include "memory.h"
#include "crt.h"
#include "linked_list.h"

namespace ick{
	Allocator * g_static_allocator = NULL;
	
	Allocator::~Allocator(){
	}
	void * Allocator::AllocateDebug(size_t size, size_t alignment, const char * format,...){
		return Allocate(size, alignment);
	}
		
	MallocAllocator::~MallocAllocator(){
		
	}
	void * MallocAllocator::Allocate(size_t size, size_t alignment){
		return malloc(size);
	}
	void MallocAllocator::Free(void * memory){
		free(memory);
	}

	const int32_t DebugAllocator::kHeadSignature = 0xBADDCAFE;
	const int32_t DebugAllocator::kFootSignature = 0xDEADBEEF;
	
	void * DebugAllocator::BlockGetUserAddress(void * block, size_t alignment){
		return Align(Offset(block, sizeof(Node *) + sizeof(int32_t)), alignment);
	}
	void DebugAllocator::NodeWriteNodeAddress(Node * node){
		Copy(&node, Offset(node->value().user, -4-(int)sizeof(Node*)), sizeof(Node*));
	}
	DebugAllocator::Node * DebugAllocator::NodeFromUserAddress(void * user){
		Node * node;
		Copy(Offset(user, -4-(int)sizeof(Node*)), &node, sizeof(Node*));
		return node;
	}
	int32_t DebugAllocator::NodeReadHeadSignature(Node * node){
		int32_t signature;
		Copy(Offset(node->value().user, -4), &signature, 4);
		return signature;
	}
	void DebugAllocator::NodeWriteHeadSignature(Node * node){
		Copy(&kHeadSignature, Offset(node->value().user, -4), 4);
	}
	int32_t DebugAllocator::NodeReadFootSignature(Node * node){
		int32_t signature;
		Copy(Offset(node->value().user, (int)node->value().size), &signature, 4);
		return signature;
	}
	void DebugAllocator::NodeWriteFootSignature(Node * node){
		Copy(&kFootSignature, Offset(node->value().user, (int)node->value().size), 4);
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
		
		size_t alloc_size = sizeof(Node *) + 4 + size + 4;
		
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
		ick::Allocator * allocator = g_static_allocator;
		g_static_allocator = allocator_;
		
		for(Node * node = info_list_->first(); node; node = node->next()){
			ICK_LOG_INFO("block: %p, user: %p, size: %zd, alignment: %zd, comment: %s",
						 node->value().block,node->value().user,
						 node->value().size,node->value().alignment,
						 node->value().comment);
		}
		
		g_static_allocator = allocator;
	}
	
	DebugAllocator * StaticDebugAllocator(){
		return static_cast<DebugAllocator *>(g_static_allocator);
	}
}