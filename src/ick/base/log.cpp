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

#ifdef ICK_WINDOWS
#	include "../windows/tchar.h"
#endif

namespace ick{
	
	void LogPut(enum LogLevel level, const char * str){
		FILE * stream = NULL;
		if (level == LogLevelInfo){
			stream = stdout;
		}else if (level == LogLevelError){
			stream = stderr;
		}

		switch (level) {
			case LogLevelInfo:
			case LogLevelError:{
#ifdef ICK_WINDOWS
				char * strSjis = WindowsAStrToAStr(str, CP_UTF8, 932);
				str = strSjis;
#endif

				int status = fputs(str, stream);
				if (status == EOF){ ::abort(); }
#ifdef ICK_WINDOWS
				ICK_FREE(strSjis);
#endif
				break;
			}
		}
	}
	void LogPrint(enum LogLevel level, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		LogPrintV(level, format, ap);
		va_end(ap);
	}
	void LogPrintV(enum LogLevel level, const char * format, va_list ap){
		LogPrintAV(static_allocator(), level, format, ap);
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
