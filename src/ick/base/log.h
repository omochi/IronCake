//
//  log.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

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

#define ICK_LOG_PRINT(level, format, ...) ICK_LOG_CALL1(ick::LogPrint, level, format, ##__VA_ARGS__)
#define ICK_LOG_PRINT_A(allocator, level, format, ...) ICK_LOG_CALL2(ick::LogPrintA, allocator, level, format, ##__VA_ARGS__)

#define ICK_LOG_INFO(format, ...) ICK_LOG_PRINT(ick::LogLevelInfo, format, ##__VA_ARGS__)
#define ICK_LOG_INFO_A(allocator, format, ...) ICK_LOG_PRINT_A(allocator, ick::LogLevelInfo, format, ##__VA_ARGS__)
#define ICK_LOG_ERROR(format, ...) ICK_LOG_PRINT(ick::LogLevelError, format, ##__VA_ARGS__)
#define ICK_LOG_ERROR_A(allocator, format, ...) ICK_LOG_PRINT_A(allocator, ick::LogLevelError, format, ##__VA_ARGS__)


namespace ick{
	class Allocator;
	
	enum LogLevel {
		LogLevelInfo,
		LogLevelError
	};
	
	void LogPut(enum LogLevel level, const char * str);
	void LogPrint(enum LogLevel level, const char * format, ...) ICK_PRINTF_LIKE(2, 3);
	void LogPrintV(enum LogLevel level, const char * format, va_list ap) ICK_PRINTF_LIKE(2, 0);
	void LogPrintA(Allocator * allocator, enum LogLevel level, const char * format, ...) ICK_PRINTF_LIKE(3, 4);
	void LogPrintAV(Allocator * allocator, enum LogLevel level, const char * format, va_list ap) ICK_PRINTF_LIKE(3, 0);
}
