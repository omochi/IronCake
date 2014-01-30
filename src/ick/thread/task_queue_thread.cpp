#include "task_queue_thread.h"

#include "scoped_lock.h"

namespace ick{
	Function<void (*)()> TaskQueueThread::PickTask(){
		Function<void (*)()> task;
		ICK_SCOPED_LOCK(mutex_);

		while(true){
			if(task_queue_.num() > 0){
				task = task_queue_.first()->value();
				task_queue_.Remove(task_queue_.first());
				break;
			}
			mutex_.Wait();
		}
		return task;
	}
	
	void TaskQueueThread::Quit(){
		do_quit_ = true;
	}
	
	TaskQueueThread::TaskQueueThread():
	do_quit_(false){
		
	}
	TaskQueueThread::~TaskQueueThread(){
		
	}
	void TaskQueueThread::Run(){
		while(!do_quit_){
			Function<void (*)()> task = PickTask();
			task();
		}
	}
	
	void TaskQueueThread::PostTask(const Function<void (*)()> & task){
		ICK_SCOPED_LOCK(mutex_);
		task_queue_.InsertLast(task);
		mutex_.Signal();
	}
	
	void TaskQueueThread::PostQuit(){
		PostTask(FunctionMake(this, &TaskQueueThread::Quit));
	}
	
	
}
