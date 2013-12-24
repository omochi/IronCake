#pragma once

#include "../base/platform.h"
#include "../base/string.h"

#ifdef ICK_WINDOWS
#	include <Windows.h>
#	include <tchar.h>
#endif

namespace ick{
	//AtoT
	TCHAR * WindowsAStrToTStr(const char * cstr, UINT code_page);
	TCHAR * WindowsAStrToTStr(char * cstr, UINT code_page, bool release);

	//AtoW
	WCHAR * WindowsAStrToWStr(const char * cstr, UINT code_page);
	WCHAR * WindowsAStrToWStr(char * cstr, UINT code_page, bool release);

	//AtoAはencoding変換
	//CopyはCStrCopyでできる
	CHAR * WindowsAStrToAStr(const char * cstr, UINT code_page, UINT dest_code_page);
	CHAR * WindowsAStrToAStr(char * cstr, UINT code_page, bool release, UINT dest_code_page);

	//WtoT
	TCHAR * WindowsWStrToTStr(const WCHAR * wstr);
	TCHAR * WindowsWStrToTStr(WCHAR * wstr, bool release);

	//WtoWはコピー
	WCHAR * WindowsWStrCopy(const WCHAR * wstr);
	WCHAR * WindowsWStrCopy(WCHAR * wstr, bool release);

	//WtoA
	CHAR * WindowsWStrToAStr(const WCHAR * wstr, UINT dest_code_page);
	CHAR * WindowsWStrToAStr(WCHAR * wstr, bool release, UINT dest_code_page);

	//TtoTはコピー
	TCHAR * WindowsTStrCopy(const TCHAR * tstr);
	TCHAR * WindowsTStrCopy(TCHAR * tstr, bool release);

	//TtoW
	WCHAR * WindowsTStrToWStr(const TCHAR * tstr);
	WCHAR * WindowsTStrToWStr(TCHAR * tstr, bool release);

	//TtoA
	CHAR * WindowsTStrToAStr(const TCHAR * tstr, UINT dest_code_page);
	CHAR * WindowsTStrToAStr(TCHAR * tstr, bool release, UINT dest_code_page);

	//TCHAR * StringToWindowsTChar(const String & string);
	//WCHAR * StringToWindowsWChar(const String & string);

	//String WindowsTCharToString(TCHAR * tstr, bool release);
	//String WindowsWCharToString(TCHAR * wstr, bool release);

}

