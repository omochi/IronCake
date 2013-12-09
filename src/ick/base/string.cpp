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
		return chars_.items();
	}
	char * String::cstr(){
		return chars_.items();
	}
	
	const char & String::operator [] (int index) const{
		return (*const_cast<String *>(this))[index];
	}
	char & String::operator [] (int index){
		ICK_ASSERT_A(allocator(), 0 <= index && index < num());
		return chars_[index];
	}
	bool String::operator == (const String & cmp) const{
		if(num() != cmp.num()){ return false; }
		for(int i = 0; i < num(); i++){
			if(chars_[i] != cmp.chars_[i]){ return false; }
		}
		return true;
	}
	
	void String::Clear(){
		chars_.set_num(1);
		chars_[0] = '\0';
	}
	
	void String::Splice(int index, int remove_num, const char * insert_chars, int insert_num){
		int num = this->num();
		ICK_ASSERT_A(allocator(), 0 <= index && index <= num);
		ICK_ASSERT_A(allocator(), 0 <= remove_num);
		ICK_ASSERT_A(allocator(), index + remove_num <= num);
		chars_.Splice(index, remove_num, insert_chars, insert_num);
	}
	
	void String::Splice(int index, int remove_num, const String & str){
		Splice(index, remove_num, str.cstr(), str.num());
	}
	void String::Append(const char * chars, int num){
		Splice(this->num(), 0, chars, num);
	}
	void String::Append(const String & str){
		Splice(num(), 0, str);
	}
	void String::Insert(int index, const char * chars, int num){
		Splice(index, 0, chars, num);
	}
	void String::Insert(int index, const String & str){
		Splice(index, 0, str);
	}
	void String::Remove(int index, int num){
		Splice(index, num, NULL, 0);
	}
	void String::Remove(int index){
		Splice(index, 1, NULL, 0);
	}
}

