//
//  array.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/07.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include "memory.h"
#include "assert.h"

namespace ick{
	template <typename T> class Array {
		Allocator * allocator_;
		T * items_;
		int alloc_num_;
		int num_;
		void set_alloc_num(int alloc_num){
			if(alloc_num_ != alloc_num_){
				T * items;
				if(alloc_num > 0){
					items = ICK_ALLOC_A(allocator_, T, alloc_num);
				}else{
					items = NULL;
				}
				int copy_num;
				if(alloc_num_ < alloc_num){
					copy_num = alloc_num_;
				}else{
					copy_num = alloc_num;
				}
				for(int i = 0; i < copy_num; i++){
					new ((void *)(items + i)) T(items_[i]);
				}
				for(int i = copy_num; i < alloc_num; i++){
					new ((void *)(items + i)) T();
				}
				for(int i = 0; i < alloc_num_; i++){
					(items_ + i)->~T();
				}
				ICK_FREE_A(allocator_, items_);
				
				items_ = items;
				alloc_num_ = alloc_num;
			}
		}
	public:
		Array():
		allocator_(g_static_allocator),items_(NULL),alloc_num_(0),num_(0){
		}
		Array(Allocator * allocator):
		allocator_(allocator),items_(NULL),alloc_num_(0),num_(0){
		}
		Array(int num):
		allocator_(g_static_allocator),items_(NULL),alloc_num_(0),num_(0){
			set_num(num);
		}
		Array(T * items, int num):
		allocator_(g_static_allocator),items_(NULL),alloc_num_(0),num_(0){
			set_num(num);
			for(int i = 0; i < num; i++){ items_[i] = items[i]; }
		}
		Array(const Array & copy):
		allocator_(g_static_allocator),items_(NULL),alloc_num_(0),num_(0){
			*this = copy;
		}
		~Array(){
			set_alloc_num(0);
		}
		
		Array<T> & operator = (const Array & copy){
			set_num(copy.num_);
			for(int i = 0; i < num_; i++){ items_[i] = copy.items_[i]; }
		}
		
		const T & operator [] (int index) const {
			return (*const_cast< Array<T> * >(this))[index];
		}
		T & operator [] (int index) {
			ICK_ASSERT_A(allocator_, 0 <= index);
			ICK_ASSERT_A(allocator_, index < num_);
			return items_[index];
		}
		
		bool operator == (const Array & cmp) const {
			if(num_ != cmp.num_){ return false; }
			for(int i = 0; i < num_; i++){
				if(items_[i] != cmp.items_[i]){ return false; }
			}
			return true;
		}
		bool operator != (const Array & cmp) const { return ! (*this == cmp); }
		
		int num() const { return num_; }
		void set_num(int num){
			if(num > alloc_num_){
				//拡大は丁度に拡大
				set_alloc_num(num);
			}else if(num * 2 + 8 < alloc_num_){
				//半分ちょい下まで減らすなら縮退させる
				set_alloc_num(alloc_num_ / 2);
			}
			num_ = num;
		}
	};
}
