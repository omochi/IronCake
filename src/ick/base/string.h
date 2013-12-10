//
//  string.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/09.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include "allocator.h"
#include "cstr.h"
#include "crt.h"
#include "array.h"

namespace ick{
	class String {
		Array<char> chars_;
	public:
		String();
		String(Allocator * allocator);
		explicit String(int num);
		explicit String(const char * cstr);
		String(const char * chars, int num);
		String(const String & value);
		virtual ~String();
		String & operator = (const String & value);
		
		Allocator * allocator() const;
		int num() const;
		void set_num(int num);
		
		const char * cstr() const;
		char * cstr();
		
		const char & operator [] (int index) const;
		char & operator [] (int index);
		
		bool operator == (const String & cmp) const;
		bool operator != (const String & cmp) const { return ! (* this == cmp); }
		
		String Slice(int index, int num) const;
		
		void Clear();
		void Set(const char * chars, int num);
		void Set(const String & value);

		
		void Splice(int index, int remove_num, const char * insert_chars, int insert_num);
		void Splice(int index, int remove_num, const String & insert_str);
		void Append(const char * chars, int num);
		void Append(const String & str);
		
		void Insert(int index, const char * chars, int num);
		void Insert(int index, const String & str);
		void Remove(int index, int num);
		void Remove(int index);
		
		static String Format(const char * format, ...) ICK_PRINTF_LIKE(1, 2);
		static String FormatV(const char * format, va_list ap) ICK_PRINTF_LIKE(1, 0);
		static String FormatA(Allocator * allocator, const char * format, ...) ICK_PRINTF_LIKE(2, 3);
		static String FormatAV(Allocator * allocator, const char * format, va_list ap) ICK_PRINTF_LIKE(2, 0);
	};
	
}