#include "error.h"

#include "../base/abort.h"
#include "../base/cstr.h"

#include <string.h>

namespace ick{
	String ErrorNumberGetDescription(ErrorNumber error_number){
		char buf[1024];
		int error_number2 = strerror_r(error_number, buf, sizeof(buf));
		if(error_number2){ ICK_ABORT("strerror_r: %d\n", error_number2); }
		return String(buf);
	}
	
	void ErrorNumberAbort(ErrorNumber error_number, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		ErrorNumberAbortV(error_number, format, ap);
		va_end(ap);
	}
	
	void ErrorNumberAbortV(ErrorNumber error_number, const char * format, va_list ap){
		String format2 = String::Format("%s: %d\n",format, error_number);
		AbortV(format2.cstr(), ap);
	}
}