//
//  fatal.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/04.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include "macro.h"
#include "log.h"

#define ICK_ABORT(format, ...) ICK_LOG_CALL0(ick::Abort, format, ##__VA_ARGS__)

namespace ick{
	void Abort(const char * format, ...) ICK_PRINTF_LIKE(1, 2);
	void AbortV(const char * format, va_list ap) ICK_PRINTF_LIKE(1, 0);
}

