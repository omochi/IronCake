#include "error.h"

#include "../base/abort.h"
#include "../base/cstr.h"

#include <string.h>

namespace ick{
	String ErrorNumberGetDescription(int error_number){
		char buf[1024];
#ifdef ICK_WINDOWS
		int error_number2 = strerror_s(buf, ICK_ARRAY_SIZE(buf), error_number);
		if (error_number2){ ICK_ABORT("strerror_s: %d\n", error_number2); }
#else
		int error_number2 = strerror_r(error_number, buf, sizeof(buf));
		if(error_number2){ ICK_ABORT("strerror_r: %d\n", error_number2); }
#endif
		return String(buf);
	}
	
	void ErrorNumberAbort(int error_number, const char * format, ...){
		va_list ap;
		va_start(ap, format);
		ErrorNumberAbortV(error_number, format, ap);
		va_end(ap);
	}
	
	void ErrorNumberAbortV(int error_number, const char * format, va_list ap){
		String format2 = String::Format("%s: %d(%s)\n",format, error_number, ErrorNumberGetDescription(error_number).cstr());
		AbortV(format2.cstr(), ap);
	}
}