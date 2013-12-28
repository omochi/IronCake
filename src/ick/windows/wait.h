#pragma once

#include "../base/platform.h"
#include "../base/string.h"

#ifdef ICK_WINDOWS
#	include <Windows.h>
#endif

namespace ick{
#ifdef ICK_WINDOWS
	//object番号ではない場合、-1を返す。
	int WindowsWaitResultGetObjectIndex(DWORD result, int num);
	int WindowsWaitResultGetAbandonedIndex(DWORD result, int num);
	String WindowsWaitResultGetDescription(DWORD result, int num);
#endif
}