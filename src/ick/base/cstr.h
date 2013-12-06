//
//  cstr.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/04.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

namespace ick{
	class Allocator;

	int CStrLen(const char * str);
	
	//free
	char * CStrCopy(const char * str);
	char * CStrCopyA(Allocator * allocator, const char * str);
	
	char * CStrAppend(const char * str1, const char * str2);
	char * CStrAppendA(Allocator * allocator, const char * str1, const char * str2);

	
}
