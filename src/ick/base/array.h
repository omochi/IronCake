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

#include "array_decl.h"

namespace ick{
	template <typename T> class Array {
		Allocator * allocator_;
		T * items_;
		int alloc_num_;
		int num_;
		void set_alloc_num(int alloc_num){
			if(alloc_num_ != alloc_num){
				T * items;
				if(alloc_num > 0){
					items = ICK_ALLOC_A(allocator_, T, alloc_num);
					
					int copy_num;
					if(alloc_num_ < alloc_num){
						copy_num = alloc_num_;
					}else{
						copy_num = alloc_num;
					}
					if(items_){
						for(int i = 0; i < copy_num; i++){
							new ((void *)(items + i)) T(items_[i]);
						}
					}
					for(int i = copy_num; i < alloc_num; i++){
						new ((void *)(items + i)) T();
					}
				}else{
					items = NULL;
				}

				if(items_){
					for(int i = 0; i < alloc_num_; i++){
						(items_ + i)->~T();
					}
					ICK_FREE_A(allocator_, items_);
				}
				
				items_ = items;
				alloc_num_ = alloc_num;
			}
		}
	public:
		Array():
		allocator_(g_static_allocator),items_(NULL),alloc_num_(0),num_(0){
		}
		explicit Array(Allocator * allocator):
		allocator_(allocator),items_(NULL),alloc_num_(0),num_(0){
		}
		explicit Array(int num):
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
			return * this;
		}
		
		const T & operator [] (int index) const {
			return (*const_cast< Array<T> * >(this))[index];
		}
		T & operator [] (int index) {
			ICK_ASSERT_A(allocator_, 0 <= index && index < num_);
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
		
		Allocator * allocator() const { return allocator_; }
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
		const T * items() const { return items_; }
		T * items() { return items_; }
		
		void Reserve(int num){
			if(alloc_num_ * 2 >= num){
				set_alloc_num(alloc_num_ * 2);
			}else{
				set_alloc_num(num);
			}
		}
		
		Array<T> Slice(int index, int num){
			ICK_ASSERT_A(allocator_, 0 <= index && index <= num_);
			ICK_ASSERT_A(allocator_, 0 <= num);
			ICK_ASSERT_A(allocator_, index + num <= num_);
			Array<T> r;
			r.set_num(num);
			for(int i = 0; i < num; i++){
				r[i] = items_[index + i];
			}
			return r;
		}
		
		void Splice(int index, int remove_num, const T * insert_items, int insert_num){
			ICK_ASSERT_A(allocator_, 0 <= index && index <= num_);
			ICK_ASSERT_A(allocator_, 0 <= remove_num);
			ICK_ASSERT_A(allocator_, index + remove_num <= num_);
			ICK_ASSERT_A(allocator_, 0 <= insert_num);
			int num_delta = insert_num - remove_num;
			int new_num = num_ + num_delta;
			if(num_delta > 0){
				Reserve(new_num);
				set_num(new_num);
				for(int i = new_num - 1; i >= index + insert_num; i--){
					items_[i] = items_[i-num_delta];
				}
			}
			for(int i = 0; i < insert_num ; i++){
				items_[index + i] = insert_items[i];
			}
			if(num_delta < 0){
				for(int i = index + insert_num; i <= new_num - 1; i++){
					items_[i] = items_[i-num_delta];
				}
				set_num(new_num);
			}
		}
		
		void Splice(int index, int remove_num, const Array<T> & insert_array){
			Splice(index, remove_num, insert_array.items(), insert_array.num());
		}
		void Append(const T & a){
			Splice(num_, 0, &a, 1);
		}
		void Append(const Array<T> & a){
			Splice(num_, 0, a);
		}
		void Insert(int index, const T & a){
			Splice(index, 0, &a, 1);
		}
		void Insert(int index, const Array<T> & a){
			Splice(index, 0, a);
		}
		void Remove(int index, int num){
			Splice(index, num, NULL, 0);
		}
		void Remove(int index){
			Splice(index, 1, NULL, 0);
		}
	};
		
	template <typename T> Array<T> ArrayMake1(const T & a1){
		T array_[] = { a1 };
		return Array<T>(array_,ICK_ARRAY_SIZE(array_));
	}
	template <typename T> Array<T> ArrayMake2(const T & a1,const T & a2){
		T array_[] = { a1,a2 };
		return Array<T>(array_,ICK_ARRAY_SIZE(array_));
	}
	template <typename T> Array<T> ArrayMake3(const T & a1,const T & a2,const T & a3){
		T array_[] = { a1,a2,a3 };
		return Array<T>(array_,ICK_ARRAY_SIZE(array_));
	}
	template <typename T> Array<T> ArrayMake4(const T & a1,const T & a2,const T & a3,const T & a4){
		T array_[] = { a1,a2,a3,a4 };
		return Array<T>(array_,ICK_ARRAY_SIZE(array_));
	}
	template <typename T> Array<T> ArrayMake5(const T & a1,const T & a2,const T & a3,const T & a4,const T & a5){
		T array_[] = { a1,a2,a3,a4,a5 };
		return Array<T>(array_,ICK_ARRAY_SIZE(array_));
	}
	template <typename T> Array<T> ArrayMake6(const T & a1,const T & a2,const T & a3,const T & a4,const T & a5,const T & a6){
		T array_[] = { a1,a2,a3,a4,a5,a6 };
		return Array<T>(array_,ICK_ARRAY_SIZE(array_));
	}
	template <typename T> Array<T> ArrayMake7(const T & a1,const T & a2,const T & a3,const T & a4,const T & a5,const T & a6,const T & a7){
		T array_[] = { a1,a2,a3,a4,a5,a6,a7 };
		return Array<T>(array_,ICK_ARRAY_SIZE(array_));
	}
	template <typename T> Array<T> ArrayMake8(const T & a1,const T & a2,const T & a3,const T & a4,const T & a5,const T & a6,const T & a7,const T & a8){
		T array_[] = { a1,a2,a3,a4,a5,a6,a7,a8 };
		return Array<T>(array_,ICK_ARRAY_SIZE(array_));
	}
}
