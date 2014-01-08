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

#ifdef ICK_ANDROID
#	include <android/log.h>
#endif

namespace ick{
	
#ifdef ICK_ANDROID
	void LogPut(enum LogLevel level, const char * str){
		int prio;
		switch (level) {
			case LogLevelInfo:
				prio = ANDROID_LOG_INFO;
				break;
			case LogLevelError:
				prio = ANDROID_LOG_ERROR;
				break;
		}
		__android_log_write(prio, "IronCake", str);
	}
#else
	void LogPut(enum LogLevel level, const char * str){
		FILE * stream = NULL;

		switch (level) {
			case LogLevelInfo:
				stream = stdout;
				break;
			case LogLevelError:
				stream = stderr;
				break;
		}

#ifdef ICK_WINDOWS
		char * strSjis = WindowsAStrToAStr(str, CP_UTF8, 932);
		str = strSjis;
#endif
		
		int status = fputs(str, stream);
		if (status == EOF){ ::abort(); }
		
#ifdef ICK_WINDOWS
		ICK_FREE(strSjis);
#endif
	}
#endif
	
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
