#include "tchar.h"
#include "../base/cstr.h"
#include "../base/abort.h"

namespace ick{
	TCHAR * WindowsAStrToTStr(const CHAR * astr, UINT code_page){
		return WindowsAStrToTStr(const_cast<CHAR *>(astr), code_page, false);
	}
	TCHAR * WindowsAStrToTStr(CHAR * astr, UINT code_page, bool release){
#ifdef UNICODE
		return WindowsAStrToWStr(astr, code_page, release);
#else
		return WindowsAStrToAStr(astr, code_page, release, CP_ACP);
#endif
	}

	WCHAR * WindowsAStrToWStr(const CHAR * astr, UINT code_page){
		return WindowsAStrToWStr(const_cast<CHAR *>(astr), code_page, false);
	}
	WCHAR * WindowsAStrToWStr(CHAR * astr, UINT code_page, bool release){
		int num = MultiByteToWideChar(code_page, 0, astr, -1, NULL, 0);
		if (num == 0){
			DWORD error = GetLastError();
			ICK_ABORT("MultiByteToWideChar: %d\n", error);
		}
		WCHAR * buf = ICK_ALLOC(WCHAR, num);
		num = MultiByteToWideChar(code_page, 0, astr, -1, buf, num);
		if (num == 0){
			DWORD error = GetLastError();
			ICK_ABORT("MultiByteToWideChar: %d\n", error);
		}
		if (release) { ICK_FREE(astr); }
		return buf;
	}

	CHAR * WindowsAStrToAStr(const CHAR * astr, UINT code_page, UINT dest_code_page){
		return WindowsAStrToAStr(const_cast<CHAR *>(astr), code_page, false, dest_code_page);
	}
	CHAR * WindowsAStrToAStr(CHAR * astr, UINT code_page, bool release, UINT dest_code_page){
		WCHAR * wstr = WindowsAStrToWStr(astr, code_page, release);
		return WindowsWStrToAStr(wstr, true, dest_code_page);
	}

	TCHAR * WindowsWStrToTStr(const WCHAR * wstr){
		return WindowsWStrToTStr(const_cast<WCHAR *>(wstr), false);
	}
	TCHAR * WindowsWStrToTStr(WCHAR * wstr, bool release){
#ifdef UNICODE
		return WindowsWStrCopy(wstr, release);
#else
		return WindowsWStrToAStr(wstr, release, CP_ACP);
#endif
	}

	WCHAR * WindowsWStrCopy(const WCHAR * wstr){
		return WindowsWStrCopy(const_cast<WCHAR *>(wstr), false);
	}
	WCHAR * WindowsWStrCopy(WCHAR * wstr, bool release){
		int n = wcslen(wstr) + 1;
		WCHAR * buf = ICK_ALLOC(WCHAR, n);
		for (int i = 0; i < n; i++){
			buf[i] = wstr[i];
		}
		if (release){ ICK_FREE(wstr); }
		return buf;
	}

	CHAR * WindowsWStrToAStr(const WCHAR * wstr, UINT dest_code_page){
		return WindowsWStrToAStr(const_cast<WCHAR *>(wstr), false, dest_code_page);
	}
	CHAR * WindowsWStrToAStr(WCHAR * wstr, bool release, UINT dest_code_page){
		int num = WideCharToMultiByte(dest_code_page, 0, wstr, -1,
			NULL, 0, NULL, NULL);
		if (num == 0){
			DWORD error = GetLastError();
			ICK_ABORT("WideCharToMultiByte: %d\n", error);
		}
		CHAR * buf = ICK_ALLOC(CHAR, num);
		num = WideCharToMultiByte(dest_code_page, 0, wstr, -1,
			buf, num, NULL, NULL);
		if (num == 0){
			DWORD error = GetLastError();
			ICK_ABORT("MultiByteToWideChar: %d\n", error);
		}
		if (release){ ICK_FREE(wstr); }
		return buf;
	}

	TCHAR * WindowsTStrCopy(const TCHAR * tstr){
		return WindowsTStrCopy(const_cast<TCHAR *>(tstr), false);
	}
	TCHAR * WindowsTStrCopy(TCHAR * tstr, bool release){
#ifdef UNICODE
		return WindowsWStrCopy(tstr, release);
#else
		return CStrCopy(tstr, release);
#endif
	}

	WCHAR * WindowsTStrToWStr(const TCHAR * tstr){
		return WindowsTStrToWStr(const_cast<TCHAR *>(tstr), false);
	}
	WCHAR * WindowsTStrToWStr(TCHAR * tstr, bool release){
#ifdef UNICODE
		return WindowsWStrCopy(tstr, release);
#else
		return WindowsAStrToWStr(tstr, CP_ACP, release);
#endif
	}

	CHAR * WindowsTStrToAStr(const TCHAR * tstr, UINT dest_code_page){
		return WindowsTStrToAStr(const_cast<TCHAR *>(tstr), false, dest_code_page);
	}
	CHAR * WindowsTStrToAStr(TCHAR * tstr, bool release, UINT dest_code_page){
#ifdef UNICODE
		return WindowsWStrToAStr(tstr, release, dest_code_page);
#else
		return WindowsAStrToAStr(tstr, CP_ACP, release, dest_code_page);
#endif
	}

	TCHAR * StringToWindowsTStr(const String & string){
		return WindowsAStrToTStr(string.cstr(), CP_UTF8);
	}

	WCHAR * StringToWindowsWStr(const String & string){
		return WindowsAStrToWStr(string.cstr(), CP_UTF8);
	}

	CHAR * StringToWindowsAStr(const String & string, UINT dest_code_page){
		return WindowsAStrToAStr(string.cstr(), CP_UTF8, dest_code_page);
	}

	String WindowsTStrToString(const TCHAR * tstr){
		return WindowsTStrToString(const_cast<TCHAR *>(tstr), false);
	}
	String WindowsTStrToString(TCHAR * tstr, bool release){
		char * cstr = WindowsTStrToAStr(tstr, release, CP_UTF8);
		String str(cstr);
		ICK_FREE(cstr);
		return str;
	}

	String WindowsWStrToString(const WCHAR * wstr){
		return WindowsWStrToString(const_cast<WCHAR *>(wstr), false);
	}
	String WindowsWStrToString(WCHAR * wstr, bool release){
		char * cstr = WindowsWStrToAStr(wstr, release, CP_UTF8);
		String str(cstr);
		ICK_FREE(cstr);
		return str;
	}

	String WindowsAStrToString(const CHAR * astr, UINT code_page){
		return WindowsAStrToString(const_cast<CHAR *>(astr), code_page, false);
	}
	String WindowsAStrToString(CHAR * astr, UINT code_page, bool release){
		char * cstr = WindowsAStrToAStr(astr, code_page, release, CP_UTF8);
		String str(cstr);
		ICK_FREE(cstr);
		return str;
	}

}

