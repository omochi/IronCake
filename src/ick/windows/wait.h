#pragma once

#include "../base/platform.h"
#include "../base/string.h"

#include <Windows.h>

namespace ick{
	//object番号ではない場合、-1を返す。
	int WindowsWaitResultGetObjectIndex(DWORD result, int num);
	int WindowsWaitResultGetAbandonedIndex(DWORD result, int num);
	String WindowsWaitResultGetDescription(DWORD result, int num);
}