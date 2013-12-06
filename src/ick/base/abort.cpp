//
//  fatal.cpp
//  IronCake
//
//  Created by おもちメタル on 2013/12/04.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "abort.h"
#include "allocator.h"

namespace ick{
	void Abort(const char * format, ...) {
		va_list ap;
		va_start(ap, format);
		ick::AbortV(format, ap);
		va_end(ap);
	}
	void AbortV(const char * format, va_list ap) {
		AbortVA(g_static_allocator, format, ap);
	}
	
	void AbortA(Allocator * allocator, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		ick::AbortVA(allocator, format, ap);
		va_end(ap);
	}
	void AbortVA(Allocator * allocator, const char * format, va_list ap){
		ick::LogPrintVA(allocator, LogLevelError, format, ap);
		::abort();
	}
}