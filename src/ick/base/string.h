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
#include "array.h"

namespace ick{
	class String {
		Array<char> chars_;
	public:
		String();
		String(Allocator * allocator);
		explicit String(const char * cstr);
		String(const String & copy);
		virtual ~String();
		String & operator = (const String & copy);
		
		Allocator * allocator() const;
		int num() const;
		const char * cstr() const;
		char * cstr();
		
		const char & operator [] (int index) const;
		char & operator [] (int index);
		
		bool operator == (const String & cmp) const;
		bool operator != (const String & cmp) const { return ! (* this == cmp); }
				
		void Clear();
		
		void Splice(int index, int remove_num, const char * insert_chars, int insert_num);
		void Splice(int index, int remove_num, const String & insert_str);
		void Append(const char * chars, int num);
		void Append(const String & str);
		void Insert(int index, const char * chars, int num);
		void Insert(int index, const String & str);
		void Remove(int index, int num);
		void Remove(int index);
		
	};
	
}