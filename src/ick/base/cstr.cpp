//
//  cstr.cpp
//  IronCake
//
//  Created by おもちメタル on 2013/12/04.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "cstr.h"

#include "memory.h"

namespace ick{
	int CStrLen(const char * str){
		int len = 0;
		const char * p = str;
		while(p[0] != '\0'){ len++; }
		return len;
	}
	char * CStrCopyA(Allocator * allocator, const char * str){
		int len = CStrLen(str);
		char * ret_str = ICK_ALLOC_A(allocator, char, len + 1);
		for(int i = 0; i < len; i++){ ret_str[i] = str[i]; }
		ret_str[len] = '\0';
		return ret_str;
	}
	char * CStrCopy(const char * str){
		return CStrCopyA(g_static_allocator, str);
	}
	char * CStrAppendA(Allocator * allocator, const char * str1, const char * str2){
		int len1 = CStrLen(str1);
		int len2 = CStrLen(str2);
		char * ret_str = ICK_ALLOC_A(allocator, char, len1 + len2 + 1);
		for(int i = 0; i < len1; i++){ ret_str[i] = str1[i]; }
		for(int i = 0; i < len2; i++){ ret_str[len1 + i] = str2[i]; }
		ret_str[len1+len2] = '\0';
		return ret_str;
	}
	char * CStrAppend(const char * str1, const char * str2){
		return CStrAppendA(g_static_allocator, str1, str2);
	}
}