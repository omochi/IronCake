//
//  log.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <stdarg.h>
#include "macro.h"

namespace ick{
	//下請け
	void LogPut(FILE * stream, const char * str);
	void LogPrint(FILE * stream, const char * format, ...) ICK_PRINTF_LIKE(2, 3);
	void LogPrintV(FILE * stream , const char * format, va_list ap) ICK_PRINTF_LIKE(2, 0);
	
	void LogInfo(const char * format, ...) ICK_PRINTF_LIKE(1, 2);
	void LogInfoV(const char * format, va_list ap) ICK_PRINTF_LIKE(1, 0);
	
	//N付きは改行無し
	void LogInfoN(const char * format,...) ICK_PRINTF_LIKE(1, 2);
	void LogInfoNV(const char * format, va_list ap) ICK_PRINTF_LIKE(1, 0);
	
	void LogError(const char * format, ...) ICK_PRINTF_LIKE(1, 2);
	void LogErrorV(const char * format, va_list ap) ICK_PRINTF_LIKE(1, 0);

	void LogErrorN(const char * format, ...) ICK_PRINTF_LIKE(1, 2);
	void LogErrorNV(const char * format, va_list ap) ICK_PRINTF_LIKE(1, 0);
}
