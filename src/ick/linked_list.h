//
//  ICKLinkedList.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include <stdlib.h>

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
		LinkedListNode():value_(),next_(NULL),prev_(NULL){
		}
		const T & value() const { return value_; }
		void set_value(const T & value) { value_ = value; }
		LinkedListNode<T> * next() const { return next; }
		LinkedListNode<T> * prev() const { return prev; }
	};
	
	template <typename T> class LinkedList {
	private:
		typedef LinkedListNode<T> Node;
		int num_;
		Node * first_;
		Node * last_;
		void set_first(Node * first) { first_ = first; }
		void set_last(Node * last) { last_ = last; }
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
		void InsertLast(Node * new_node){
			if(!last()){
				InsertFirst(new_node);
			}else{
				InsertAfter(last(), new_node);
			}
		}
	public:
		LinkedList():num_(0),first_(NULL),last_(NULL){
		}
		int num() const { return num_; }
		Node * first() const { return first_; }
		Node * last() const { return last_; }
		
	};
}
