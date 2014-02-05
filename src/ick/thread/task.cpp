#include "task.h"

#include "../base/memory.h"

namespace ick{
	void TaskRun(Task * task){
		(*task)(false);
		ICK_DELETE(task);
	}
	void TaskCancel(Task * task){
		(*task)(true);
		ICK_DELETE(task);
	}
}
