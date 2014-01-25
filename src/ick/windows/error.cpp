#include "error.h"

#include "../base/abort.h"
#include "tchar.h"

namespace ick{
	String WindowsErrorGetDescription(DWORD error){
		TCHAR * buf;
		DWORD ret = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 既定の言語
			reinterpret_cast<LPTSTR>(&buf), 0,
			NULL);
		if (ret == 0){ ICK_ABORT("FormatMessage\n"); }
		String desc = WindowsTStrToString(buf);
		LocalFree(buf);
		return desc;
	}
	String WindowsLastErrorGetDescription(){
		return WindowsErrorGetDescription(GetLastError());
	}
}
