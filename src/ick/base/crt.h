//
//  crt.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include "macro.h"

namespace ick {
	class Allocator;

	int printf(const char * format, ...) ICK_PRINTF_LIKE(1, 2);
	int vprintf(const char * format, va_list ap) ICK_PRINTF_LIKE(1, 0);
	
	int fprintf(FILE * stream, const char * format, ...) ICK_PRINTF_LIKE(2, 3);
	int vfprintf(FILE * stream, const char * format, va_list ap) ICK_PRINTF_LIKE(2, 0);
	
	//下請けに
	int snprintf(char * str, size_t size, const char * format, ...) ICK_PRINTF_LIKE(3, 4);
	int vsnprintf(char * str, size_t size, const char * format, va_list ap) ICK_PRINTF_LIKE(3, 0);
	
	int asprintf(Allocator * allocator, char **ret, const char * format, ...) ICK_PRINTF_LIKE(3, 4);
	int vasprintf(Allocator * allocator, char **ret, const char * format, va_list ap) ICK_PRINTF_LIKE(3, 0);
}
