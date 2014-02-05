#pragma once

#include "../function/function.h"
#include "../function/function_macro.h"

namespace ick{
	typedef ICK_FUNCTION(void, bool) Task;
	
	// その後解放する
	void TaskRun(Task * task);
	void TaskCancel(Task * task);
}
