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
		return ick::fprintf(stdout, format, ap);
	}
	
	int fprintf(FILE * stream, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		int r = ick::vfprintf(stream, format, ap);
		va_end(ap);
		return r;
	}
	int vfprintf(FILE * stream, const char * format, va_list ap){
#ifdef ICK_WINDOWS
		return ::vfprintf_s(stream, format, ap);
#else
		return ::vfprintf(stream, format, ap);
#endif
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
#ifdef ICK_WINDOWS
		if (!str){ return ::_vscprintf(format, ap); }
		return ::vsnprintf_s(str, size, _TRUNCATE, format, ap);
#else
		return ::vsnprintf(str, size, format, ap);
#endif
	}
	
	int asprintf(Allocator * allocator, char **ret, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		int r = vasprintf(allocator, ret, format, ap);
		va_end(ap);
		return r;
	}
	int vasprintf(Allocator * allocator, char **ret, const char * format, va_list ap){
		va_list ap2;
		va_copy(ap2, ap);
		int num = ick::vsnprintf(NULL, 0, format, ap2);
		va_end(ap2);
		size_t size = static_cast<size_t>(num+1);
		*ret = ICK_ALLOC_A(allocator, char, static_cast<int>(size));
		return ick::vsnprintf(*ret, size, format, ap);
	}
}