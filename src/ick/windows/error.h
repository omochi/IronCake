#pragma once

#include "../base/platform.h"
#include "../base/string.h"

#include <Windows.h>

namespace ick{
	
	String WindowsErrorGetDescription(DWORD error);
	String WindowsLastErrorGetDescription();
	
}



