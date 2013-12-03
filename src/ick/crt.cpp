//
//  crt.cpp
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "crt.h"

#include "memory.h"

namespace ick{
	int printf(const char * format, ...){
		va_list ap;
		va_start(ap, format);
		int r = vprintf(format, ap);
		va_end(ap);
		return r;
	}
	int vprintf(const char * format, va_list ap){
		return ::vprintf(format, ap);
	}
	
	int fprintf(FILE * stream, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		int r = ick::vfprintf(stream, format, ap);
		va_end(ap);
		return r;
	}
	int vfprintf(FILE * stream, const char * format, va_list ap){
		return ::vfprintf(stream, format, ap);
	}
	
	//下請けに
	int snprintf(char * str, size_t size, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		int r = vsnprintf(str, size, format, ap);
		va_end(ap);
		return r;
	}
	int vsnprintf(char * str, size_t size, const char * format, va_list ap){
		return ::vsnprintf(str, size, format, ap);
	}
	
	int asprintf(Allocator * allocator, char **ret, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		int r = vasprintf(allocator, ret, format, ap);
		va_end(ap);
		return r;
	}
	int vasprintf(Allocator * allocator, char **ret, const char * format, va_list ap){
		int num = ick::vsnprintf(NULL, 0, format, ap);
		size_t size = num + 1;
		*ret = ICK_ALLOC_A(allocator, char, size);
		int r = ick::vsnprintf(*ret, size, format, ap);
		return r;
	}
}