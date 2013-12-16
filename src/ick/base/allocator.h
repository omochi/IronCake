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

	extern Allocator * g_static_allocator;
	
	class Allocator {
	public:
		virtual ~Allocator();
		virtual void * Allocate(size_t size, size_t alignment) = 0;
		virtual void * AllocateDebug(size_t size, size_t alignment, const char * format, ...) ICK_PRINTF_LIKE(4, 5);
		virtual void Free(void * memory) = 0;
	};
	
	class MallocAllocator : public Allocator {
	public:
		virtual ~MallocAllocator();
		virtual void * Allocate(size_t size, size_t alignment);
		virtual void Free(void * memory);
	};

	template <typename T> class LinkedList;
	template <typename T> class LinkedListNode;
	
	struct DebugAllocatorBlockInfo {
		//アロケータから取ってきたアドレス
		void * block;
		//ユーザに戻すアドレス
		void * user;
		//ユーザ要求サイズ
		size_t size;
		size_t alignment;
		//コメント
		char * comment;
	};

	class DebugAllocator : public Allocator {
	public:
		typedef LinkedList<DebugAllocatorBlockInfo> List;
		typedef LinkedListNode<DebugAllocatorBlockInfo> Node;
	private:
		Allocator * allocator_;
		List * info_list_;
	public:
		Allocator * allocator() const { return allocator_; }
		List * info_list() const { return info_list_; }
		
		static const uint32_t kHeadSignature;
		static const uint32_t kFootSignature;

		static void * BlockGetUserAddress(void * block, size_t alignment);
		
		static void NodeWriteNodeAddress(Node * node);
		static Node * NodeFromUserAddress(void * user);
		static uint32_t NodeReadHeadSignature(Node * node);
		static void NodeWriteHeadSignature(Node * node);
		static uint32_t NodeReadFootSignature(Node * node);
		static void NodeWriteFootSignature(Node * node);
		static bool NodeCheckSignature(Node * node);

		DebugAllocator(Allocator * allocator);
		virtual ~DebugAllocator();
		virtual void * Allocate(size_t size, size_t alignment);
		virtual void * AllocateDebug(size_t size, size_t alignment, const char * format, ...);
		virtual void Free(void * memory);
		
		// 見つかった破損ノードを返す
		bool CheckSignatures(Node ** node);
		
		void Dump();
	};
	
	//キャスト
	DebugAllocator * StaticDebugAllocator();
	
}
