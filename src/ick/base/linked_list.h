//
//  ICKLinkedList.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include "memory.h"
#include "allocator.h"
#include "assert.h"

namespace ick{
	template <typename T> class LinkedList;
	
	template <typename T> class LinkedListNode {
		typedef LinkedList<T> List;
		friend class LinkedList<T>;
	private:
		const List * list_;
		T value_;
		LinkedListNode<T> * next_;
		LinkedListNode<T> * prev_;
	public:
		LinkedListNode():
		list_(NULL),value_(),next_(NULL),prev_(NULL)
		{
		}
		LinkedListNode(const T & value):
		list_(NULL),value_(value),next_(NULL),prev_(NULL)
		{
		}
		const T & value() const { return value_; }
		void set_value(const T & value) { value_ = value; }
		LinkedListNode<T> * next() const { return next_; }
		LinkedListNode<T> * prev() const { return prev_; }
	};
	
	template <typename T> class LinkedList {
	private:
		typedef LinkedListNode<T> Node;
		Allocator * allocator_;
		int num_;
		Node * first_;
		Node * last_;

		Node * CreateNode(const T & value) const {
			return ICK_NEW_A(allocator_, Node, value);
		}
		void InsertFirst(Node * new_node){
			ICK_ASSERT_A(allocator_, !new_node->list_);
			if(!first_){
				num_++;
				first_ = new_node;
				last_ = new_node;
				new_node->list_ = this;
			}else{
				InsertBefore(first_, new_node);
			}
		}
		void InsertLast(Node * new_node){
			ICK_ASSERT_A(allocator_,!new_node->list_);
			if(!last_){
				InsertFirst(new_node);
			}else{
				InsertAfter(last_, new_node);
			}
		}
		void InsertBefore(Node * node, Node * new_node) {
			ICK_ASSERT_A(allocator_,node->list_ == this);
			ICK_ASSERT_A(allocator_,!new_node->list_);
			num_++;
			new_node->list_ = this;
			new_node->prev_ = node->prev_;
			new_node->next_ = node;
			if(!node->prev_){
				first_ = new_node;
			}else{
				node->prev_->next_ = new_node;
			}
			node->prev_ = new_node;
		}
		void InsertAfter(Node * node, Node * new_node) {
			ICK_ASSERT_A(allocator_,node->list_ == this);
			ICK_ASSERT_A(allocator_,!new_node->list_);
			num_++;
			new_node->list_ = this;
			new_node->prev_ = node;
			new_node->next_ = node->next_;
			if(!node->next_){
				last_ = new_node;
			}else{
				node->next_->prev_ = new_node;
			}
			node->next_ = new_node;
		}
	public:
		LinkedList():
		allocator_(static_allocator()),num_(0),first_(NULL),last_(NULL)
		{
		}
		explicit LinkedList(Allocator * allocator):
		allocator_(allocator),num_(0),first_(NULL),last_(NULL)
		{
		}
		Allocator * allocator() const { return allocator_; }
		int num() const { return num_; }
		Node * first() const { return first_; }
		Node * last() const { return last_; }
		
		Node * InsertFirst(const T & value){
			Node * node = CreateNode(value);
			InsertFirst(node);
			return node;
		}
		Node * InsertLast(const T & value){
			Node * node = CreateNode(value);
			InsertLast(node);
			return node;
		}
		Node * InsertBefore(Node * node, const T & value){
			Node * new_node = CreateNode(value);
			InsertBefore(node, new_node);
			return new_node;
		}
		Node * InsertAfter(Node * node, const T & value){
			Node * new_node = CreateNode(value);
			InsertAfter(node, new_node);
			return new_node;
		}
		//nodeはdeleteされる
		void Remove(Node * node){
			ICK_ASSERT_A(allocator_, node->list_ == this);
			num_--;
			if(!node->prev_){
				first_ = node->next_;
			}else{
				node->prev_->next_ = node->next_;
			}
			if(!node->next_){
				last_ = node->prev_;
			}else{
				node->next_->prev_ = node->prev_;
			}
			ICK_DELETE_A(allocator_, node);
		}
		void Clear(){
			while(last_){ Remove(last_); }
		}
	};
}
