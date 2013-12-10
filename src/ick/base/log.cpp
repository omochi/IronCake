//
//  log.cpp
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "log.h"

#include "memory.h"
#include "crt.h"
#include "cstr.h"

namespace ick{
	
	void LogPut(enum LogLevel level, const char * str){
		switch (level) {
			case LogLevelInfo:{
				int status = fputs(str, stdout);
				if(status == EOF){ ::abort(); }
			}
				break;
			case LogLevelError:{
				int status = fputs(str, stderr);
				if(status == EOF){ ::abort(); }
			}
				break;
		}
	}
	void LogPrint(enum LogLevel level, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		LogPrintV(level, format, ap);
		va_end(ap);
	}
	void LogPrintV(enum LogLevel level, const char * format, va_list ap){
		LogPrintAV(g_static_allocator, level, format, ap);
	}
	void LogPrintA(Allocator * allocator, enum LogLevel level, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		LogPrintAV(allocator, level, format, ap);
		va_end(ap);
	}
	void LogPrintAV(Allocator * allocator, enum LogLevel level, const char * format, va_list ap){
		char * str;
		int status = ick::vasprintf(allocator, &str, format, ap);
		if(status < 0){ ::abort(); }
		LogPut(level, str);
		ICK_FREE(str);
	}
	
}
