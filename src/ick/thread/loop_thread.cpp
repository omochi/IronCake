#include "loop_thread.h"

#include "../function/function_bind.h"

namespace ick{
	bool LoopThread::PickTask(Function<void (*)()> * task){
		bool ok = true;
		mutex_.Lock();
		while(true){
			if(task_queue_.num() > 0){
				*task = task_queue_.first()->value();
				task_queue_.Remove(task_queue_.first());
				break;
			}
			mutex_.Wait();
		}
		mutex_.Unlock();
		return ok;
	}
	
	void LoopThreadQuit(LoopThread * thiz){
		thiz->do_quit_ = true;
	}
	
	LoopThread::LoopThread():
	do_quit_(false){
		
	}
	LoopThread::~LoopThread(){
		
	}
	void LoopThread::Run(){
		while(!do_quit_){
			Function<void (*)()> task;
			if(!PickTask(&task)){ continue; }
			task();
		}
	}
	
	void LoopThread::Post(const Function<void (*)()> & task){
		mutex_.Lock();
		task_queue_.InsertLast(task);
		mutex_.Notify();
		mutex_.Unlock();
	}
	
	void LoopThread::PostQuit(){
		Post(FunctionBind1(LoopThreadQuit, this));
	}
	
	
}
