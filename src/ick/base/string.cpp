//
//  string.cpp
//  IronCake
//
//  Created by おもちメタル on 2013/12/09.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "string.h"

namespace ick{
	String::String():
	chars_(){
		Clear();
	}
	String::String(Allocator * allocator):
	chars_(allocator){
		Clear();
	}
	String::String(const char * cstr):
	chars_(g_static_allocator){
		int n = CStrLen(cstr);
		chars_.set_num(n+1);
		for(int i = 0; i < n; i++){ chars_[i] = cstr[i]; }
		chars_[n] = '\0';
	}
	String::String(const String & copy){
		*this = copy;
	}
	String::~String(){
		
	}
	String & String::operator = (const String & copy){
		int n = copy.num();
		chars_.set_num(n+1);
		for(int i = 0; i < n; i++){ chars_[i] = copy[i]; }
		chars_[n] = '\0';
		return * this;
	}
	
	Allocator * String::allocator() const {
		return chars_.allocator();
	}
	
	int String::num() const {
		return chars_.num() - 1;
	}
	
	const char * String::cstr() const{
		return &chars_[0];
	}
	
	char String::operator [] (int index) const{
		return (*const_cast<String *>(this))[index];
	}
	char & String::operator [] (int index){
		ICK_ASSERT_A(allocator(), 0 <= index && index < num());
		return chars_[index];
	}
	
	void String::Clear(){
		chars_.set_num(1);
		chars_[0] = '\0';
	}
	
	void String::Splice(int index, int remove_num, const String & str){
		int n = num();
		int sn = str.num();
		ICK_ASSERT_A(allocator(), 0 <= index && index <= n);
		ICK_ASSERT_A(allocator(), 0 <= remove_num);
		ICK_ASSERT_A(allocator(), index + remove_num <= n);
		int num_delta = sn - remove_num;
		int new_num = n + num_delta;
		if(num_delta > 0){
			chars_.Reserve(new_num);
			chars_.set_num(new_num);
			for(int i = new_num - 1; i >= index + sn; i--){
				chars_[i] = chars_[i-num_delta];
			}
		}
		for(int i = 0; i < sn ; i++){
			chars_[index + i] = str.chars_[i];
		}
		if(num_delta < 0){
			for(int i = index + sn; i <= new_num - 1; i++){
				chars_[i] = chars_[i-num_delta];
			}
			chars_.set_num(new_num);
		}
	}
	
	void String::Append(const String & str){
		Splice(num(), 0, str);
	}
	void String::Insert(int index, const String & str){
		Splice(index, 0, str);
	}
	void String::Remove(int index, int num){
		//空のString作るのが嫌だ
		int n = this->num();
		ICK_ASSERT_A(allocator(), 0 <= index && index <= n);
		ICK_ASSERT_A(allocator(), 0 <= num);
		ICK_ASSERT_A(allocator(), index + num <= n);
		int num_delta = - num;
		int new_num = n + num_delta;
		if(num_delta < 0){
			for(int i = index; i <= new_num - 1; i++){
				chars_[i] = chars_[i-num_delta];
			}
			chars_.set_num(new_num);
		}
	}
	void String::Remove(int index){
		Remove(index, 1);
	}
}

