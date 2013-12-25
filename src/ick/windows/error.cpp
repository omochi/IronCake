#include "windows.h"

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
		if (ret == 0){ ICK_ABORT("FormatMessage"); }
		String desc = WindowsTStrToString(buf);
		LocalFree(buf);
		return desc;
	}
	String WindowsLastErrorGetDescription(){
		return WindowsErrorGetDescription(GetLastError());
	}
	String WindowsWaitResultGetDescription(DWORD result){
		String text;
		switch (result){
		case WAIT_ABANDONED:
			text = String("WAIT_ABANDONED");
			break;
		case WAIT_IO_COMPLETION:
			text = String("WAIT_IO_COMPLETION");
			break;
		case WAIT_OBJECT_0:
			text = String::Format("WAIT_OBJECT_0");
			break;
		case WAIT_TIMEOUT:
			text = String("WAIT_TIMEOUT");
			break;
		case WAIT_FAILED:
			text = String::Format("WAIT_FAILED: %s", WindowsLastErrorGetDescription().cstr());
			break;
		}
		text = String::Format("WaitForSingleObject: %s", text.cstr());
		return text;
	}
}
