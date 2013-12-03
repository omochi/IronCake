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

// 呼び出し箇所ダンプを挿入するやつ

#ifdef ICK_LOG_LINE_DEBUG
#	define ICK_LOG_CALL0(func, format, ...) func("[%s:%s:%d]" format, __FILE__, ICK_FUNC, __LINE__, ##__VA_ARGS__ )
#	define ICK_LOG_CALL1(func, a1, format, ...) func(a1, "[%s:%s:%d]" format, __FILE__, ICK_FUNC, __LINE__, ##__VA_ARGS__ )
#	define ICK_LOG_CALL2(func, a1, a2, format, ...) func(a1, a2, "[%s:%s:%d]" format, __FILE__, ICK_FUNC, __LINE__, ##__VA_ARGS__ )
#	define ICK_LOG_CALL3(func, a1, a2, a3, format, ...) func(a1, a2, a3, "[%s:%s:%d]" format, __FILE__, ICK_FUNC, __LINE__, ##__VA_ARGS__ )
#else
#	define ICK_LOG_CALL0(func, format, ...) func(format, ##__VA_ARGS__)
#	define ICK_LOG_CALL1(func, a1, format, ...) func(a1, format, ##__VA_ARGS__)
#	define ICK_LOG_CALL2(func, a1, a2, format, ...) func(a1, a2, format, ##__VA_ARGS__)
#	define ICK_LOG_CALL3(func, a1, a2, a3, format, ...) func(a1, a2, a3, format, ##__VA_ARGS__)
#endif

// 使う用

#define ICK_LOG_INFO(format, ...) ICK_LOG_CALL0(ick::LogInfo, format, ##__VA_ARGS__)
#define ICK_LOG_INFO_N(format, ...) ICK_LOG_CALL0(ick::LogInfoN, format, ##__VA_ARGS__)
#define ICK_LOG_ERROR(format, ...) ICK_LOG_CALL0(ick::LogError, format, ##__VA_ARGS__)
#define ICK_LOG_ERROR_N(format, ...) ICK_LOG_CALL0(ick::LogErrorN, format, ##__VA_ARGS__)

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
