#pragma once

#include "../base/platform.h"
#include "../base/string.h"

#ifdef ICK_WINDOWS
#	include <Windows.h>
#endif

namespace ick{
	
#ifdef ICK_WINDOWS
	String WindowsErrorGetDescription(DWORD error);
	String WindowsLastErrorGetDescription();
	String WindowsWaitResultGetDescription(DWORD result);
#endif 
	
}



