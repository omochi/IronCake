#pragma once

#include "allocator.h"

namespace ick{
	template <typename T> class LinkedList;
	template <typename T> class LinkedListNode;

	class String;

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
		virtual void * AllocateDebugV(size_t size, size_t alignment, const char * format, va_list ap) ICK_PRINTF_LIKE(4, 0);
		virtual void Free(void * memory);

		// 見つかった破損ノードを返す
		bool CheckSignatures(Node ** node);

		String Dump();
	};

	//キャスト
	DebugAllocator * static_debug_allocator();

}

