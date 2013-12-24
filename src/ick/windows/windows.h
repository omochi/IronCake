#pragma once

#include "../base/platform.h"
#include "../base/string.h"

#ifdef ICK_WINDOWS
#	include <Windows.h>
#endif

namespace ick{
	String WindowsErrorGetDescription(DWORD error);


}

