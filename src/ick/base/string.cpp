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
	String::String(int num):
	chars_(){
		set_num(num);
	}
	String::String(const char * cstr):
	chars_(){
		Set(cstr, CStrLen(cstr));
	}
	String::String(const char * chars, int num):
	chars_(){
		Set(chars, num);
	}
	String::String(const String & value){
		Set(value);
	}
	String::~String(){
		
	}
	String & String::operator = (const String & value){
		Set(value);
		return * this;
	}
	
	Allocator * String::allocator() const {
		return chars_.allocator();
	}
	
	int String::num() const {
		return chars_.num() - 1;
	}
	void String::set_num(int num){
		chars_.set_num(num + 1);
		chars_[num] = '\0';
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
	
	String String::Slice(int index, int num) const{
		String r(num);
		r.Splice(0, num, &chars_[index], num);
		return r;
	}
	
	void String::Clear(){
		set_num(0);
	}
	
	void String::Set(const char * chars, int num){
		set_num(num);
		Splice(0, num, chars, num);
	}
	void String::Set(const String & value){ Set(&value.chars_[0], value.num()); }
	
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
	
	String String::Format(const char * format, ...){
		va_list ap;
		va_start(ap, format);
		String r = FormatV(format, ap);
		va_end(ap);
		return r;
	}
	String String::FormatV(const char * format, va_list ap){
		return FormatAV(g_static_allocator, format, ap);
	}
	String String::FormatA(Allocator * allocator, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		String r = FormatAV(allocator, format, ap);
		va_end(ap);
		return r;
	}
	String String::FormatAV(Allocator * allocator, const char *format, va_list ap){
		char * cstr;
		int st = ick::vasprintf(allocator, &cstr, format, ap);
		if(st < 0){ ICK_ABORT_A(allocator, "vasprintf failed"); }
		String s = String(allocator);
		s.Set(cstr, CStrLen(cstr));
		ICK_FREE_A(allocator, cstr);
		return s;
	}
}

