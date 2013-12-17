#pragma once

#include <errno.h>

#include "macro.h"
#include "string.h"

#define ICK_EN_ABORT(error_number, format, ...) ICK_LOG_CALL1(ick::ErrorNumberAbort, error_number, format, ##__VA_ARGS__)

#define ICK_EN_CALL(call) {\
	ick::ErrorNumber en = call;\
	if(en){ ICK_EN_ABORT(en, #call); }\
}

namespace ick{
	typedef int ErrorNumber;
	
	String ErrorNumberGetDescription(ErrorNumber error_number);
	
	void ErrorNumberAbort(ErrorNumber error_number, const char * format, ...) ICK_PRINTF_LIKE(2, 3);
	void ErrorNumberAbortV(ErrorNumber error_number, const char * format, va_list ap) ICK_PRINTF_LIKE(2, 0);
}