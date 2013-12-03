//
//  ICKLinkedList.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include <stdlib.h>
#include "allocator.h"
#include "memory.h"

namespace ick{
	template <typename T> class LinkedList;
	
	template <typename T> class LinkedListNode {
		friend LinkedList<T>;
	private:
		T value_;
		LinkedListNode<T> * next_;
		LinkedListNode<T> * prev_;
		void set_next(const LinkedListNode<T> * next) { next_ = next; }
		void set_prev(const LinkedListNode<T> * prev) { prev_ = prev; }
	public:
		LinkedListNode():
		value_(),next_(NULL),prev_(NULL)
		{
		}
		LinkedListNode(const T & value):
		value_(value),next_(NULL),prev_(NULL)
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
		void set_first(Node * first) { first_ = first; }
		void set_last(Node * last) { last_ = last; }


	public:
		LinkedList():
		allocator_(g_static_allocator),num_(0),first_(NULL),last_(NULL)
		{
		}
		LinkedList(Allocator * allocator):
		allocator_(allocator),num_(0),first_(NULL),last_(NULL)
		{
		}
		Allocator * allocator() const { return allocator_; }
		int num() const { return num_; }
		Node * first() const { return first_; }
		Node * last() const { return last_; }
		void InsertFirst(Node * new_node){
			if(!first()){
				set_first(new_node);
				set_last(new_node);
				new_node->set_prev(NULL);
				new_node->set_next(NULL);
			}else{
				InsertBefore(first(), new_node);
			}
		}
		Node * InsertFirst(const T & value){
			Node * node = ICK_NEW_A(allocator(), Node, value);
			InsertFirst(node);
			return node;
		}
		void InsertLast(Node * new_node){
			if(!last()){
				InsertFirst(new_node);
			}else{
				InsertAfter(last(), new_node);
			}
		}
		Node * InsertLast(const T & value){
			Node * node = ICK_NEW_A(allocator(), Node, value);
			InsertLast(node);
			return node;
		}
		void InsertBefore(Node * node, Node * new_node) {
			new_node->set_prev(node->prev());
			new_node->set_next(node);
			if(!node->prev()){
				set_first(new_node);
			}else{
				node->prev()->next() = new_node;
			}
			node->set_prev(new_node);
		}
		Node * InsertBefore(Node * node, const T & value){
			Node * new_node = ICK_NEW_A(allocator(), Node, value);
			InsertBefore(node, new_node);
			return new_node;
		}
		void InsertAfter(Node * node, Node * new_node) {
			new_node->set_prev(node);
			new_node->set_next(node->next());
			if(!node->next()){
				set_last(new_node);
			}else{
				node->next()->set_prev(new_node);
			}
			node->set_next(new_node);
		}
		Node * InsertAfter(Node * node, const T & value){
			Node * new_node = ICK_NEW_A(allocator(), Node, value);
			InsertAfter(node, new_node);
			return new_node;
		}
		//nodeはdeleteされる
		void Remove(Node * node){
			if(!node->prev()){
				set_first(node->next());
			}else{
				node->prev()->set_next(node->next());
			}
			if(!node->next()){
				set_last(node->prev());
			}else{
				node->next()->set_prev(node->prev());
			}
			ICK_DELETE_A(allocator(), node);
		}
	};
}
