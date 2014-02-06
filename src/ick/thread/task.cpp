#include "task.h"

#include "../base/memory.h"
#include "../function/function_bind.h"

namespace ick{
	void TaskRun(Task * task){
		(*task)(false);
		ICK_DELETE(task);
	}
	void TaskCancel(Task * task){
		(*task)(true);
		ICK_DELETE(task);
	}
	
	Task * TaskCreate(ICK_FUNCTION(void, bool) func){
		return ICK_NEW(Task, func);
	}
	
	void TaskCreateWrapper(ICK_FUNCTION(void) func,bool skip_on_cancelled, bool cancelled){
		if(skip_on_cancelled && cancelled){
			return;
		}
		func();
	}
	
	Task * TaskCreate(ICK_FUNCTION(void) func, bool skip_on_cancelled){
		return ICK_NEW(Task, FunctionBind(TaskCreateWrapper, func, skip_on_cancelled));
	}

}
