#include "debug_allocator.h"

#include "string.h"
#include "crt.h"
#include "log.h"
#include "linked_list.h"

#include "../thread/mutex.h"
#include "../thread/scoped_lock.h"

namespace ick{

	const uint32_t DebugAllocator::kHeadSignature = 0xBADDCAFE;
	const uint32_t DebugAllocator::kFootSignature = 0xDEADBEEF;

	void * DebugAllocator::BlockGetUserAddress(void * block, size_t alignment){
		return AddressAlign(AddressOffset(block, sizeof(Node *)+sizeof(int32_t)), alignment);
	}
	void DebugAllocator::NodeWriteNodeAddress(Node * node){
		MemoryCopy(&node, AddressOffset(node->value().user, -4 - (int)sizeof(Node*)), sizeof(Node*));
	}
	DebugAllocator::Node * DebugAllocator::NodeFromUserAddress(void * user){
		Node * node;
		MemoryCopy(AddressOffset(user, -4 - (int)sizeof(Node*)), &node, sizeof(Node*));
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

	DebugAllocator::DebugAllocator(Allocator * allocator) :
	allocator_(allocator){
		info_list_ = ICK_NEW_A(allocator_, List, allocator_);
		mutex_ = ICK_NEW_A(allocator_, Mutex, allocator_);
	}
	DebugAllocator::~DebugAllocator(){
		ICK_DELETE_A(allocator_, info_list_);
		ICK_DELETE_A(allocator_, mutex_);
	}
	void * DebugAllocator::Allocate(size_t size, size_t alignment){
		return AllocateDebug(size, alignment, "");
	}
	void * DebugAllocator::AllocateDebugV(size_t size, size_t alignment,
										  const char * format, va_list ap)
	{
		ScopedLock sl(*mutex_);
		
		ICK_ASSERT(alignment > 0);

		char * comment;
		int r = vasprintf(allocator_, &comment, format, ap);
		if (r<0){ ::abort(); }

		size_t alloc_size = sizeof(Node *)+4 + (alignment - 1) + size + 4;

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
		ScopedLock sl(*mutex_);
		
		Node * node = NodeFromUserAddress(memory);
		ICK_FREE_A(allocator_, node->value().comment);
		ICK_FREE_A(allocator_, node->value().block);
		info_list_->Remove(node);
	}

	bool DebugAllocator::CheckSignatures(Node ** node){
		ScopedLock sl(*mutex_);
		
		for (Node * n = info_list_->first(); n; n = n->next()){
			if (!NodeCheckSignature(n)){
				if (node){ *node = n; }
				return false;
			}
		}
		return true;
	}

	String DebugAllocator::Dump(){
		ScopedLock sl(*mutex_);
		
		String dump(allocator_);
		for (Node * node = info_list_->first(); node; node = node->next()){
			dump.AppendFormat(
				"block: 0x%p, "
				"user: 0x%p, " 
				"size: " ICK_PRI_SIZE_T ", "
				"alignment: " ICK_PRI_SIZE_T ", "
				"comment: %s\n",
				node->value().block, 
				node->value().user,
				node->value().size, 
				node->value().alignment,
				node->value().comment);
		}
		return dump;
	}

	DebugAllocator * static_debug_allocator(){
		return static_cast<DebugAllocator *>(static_allocator());
	}
}
