//
//  log.cpp
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "log.h"

#include <stdlib.h>

#include "memory.h"
#include "crt.h"
#include "cstr.h"

namespace ick{
	void LogPut(FILE * stream, const char * str){
		int status = fputs(str, stream);
		if(status != EOF){ abort(); }
	}
	void LogPrint(FILE * stream, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		LogPrintV(stream, format, ap);
		va_end(ap);
	}
	void LogPrintV(FILE * stream , const char * format, va_list ap){
		char * ret;
		int status = ick::vasprintf(g_static_allocator, &ret, format, ap);
		if(status < 0){ abort(); }
		LogPut(stream, ret);
		ICK_FREE(ret);
	}

	void LogInfo(const char * format, ...){
		va_list ap;
		va_start(ap, format);
		LogInfoV(format, ap);
		va_end(ap);
	}
	void LogInfoV(const char * format, va_list ap){
		char * format_ln = ick::CStrAppend(format, "\n");
		LogInfoNV(format_ln, ap);
		ICK_FREE(format_ln);
	}
	
	//N付きは改行無し
	void LogInfoN(const char * format,...){
		va_list ap;
		va_start(ap, format);
		LogInfoNV(format, ap);
		va_end(ap);
	}
	void LogInfoNV(const char * format, va_list ap){
		LogPrintV(stdout, format, ap);
	}
	
	void LogError(const char * format, ...){
		va_list ap;
		va_start(ap, format);
		LogErrorV(format, ap);
		va_end(ap);
	}
	void LogErrorV(const char * format, va_list ap){
		char * format_ln = ick::CStrAppend(format, "\n");
		LogInfoNV(format_ln, ap);
		ICK_FREE(format_ln);
	}
	
	void LogErrorN(const char * format, ...){
		va_list ap;
		va_start(ap, format);
		LogErrorNV(format, ap);
		va_end(ap);
	}
	void LogErrorNV(const char * format, va_list ap){
		LogPrintV(stderr, format, ap);
	}
}
