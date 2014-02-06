#include "task_queue_thread.h"

#include "scoped_lock.h"
#include "../function/function_bind.h"

namespace ick{
	void TaskQueueThread::QuitTask(bool cancelled){
		(void)cancelled;
		do_quit_ = true;
	}
	
	TaskQueueThread::TaskQueueThread():
	do_quit_(false){
		
	}
	TaskQueueThread::~TaskQueueThread(){
		
	}
	TaskQueue * TaskQueueThread::task_queue(){
		return & task_queue_;
	}
	
	void TaskQueueThread::Run(){
		while(!do_quit_){
			task_queue_.mutex()->Lock();
				TaskRun(task_queue_.Pick());
			task_queue_.mutex()->Unlock();
		}
	}

	void TaskQueueThread::Post(Task * task){
		task_queue_.Post(task);
	}
	
	void TaskQueueThread::PostQuit(){
		Post(TaskCreate(FunctionBind(&TaskQueueThread::QuitTask, this)));
	}
	
	
}
