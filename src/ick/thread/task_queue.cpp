#include "task_queue.h"

#include "../base/abort.h"
#include "scoped_lock.h"

namespace ick{
	void TaskQueue::Cancel(LinkedListNode<Task *> * task_node){
		// タスクを探す
		Task * task = task_node->value();
		queue_.Remove(task_node);
		TaskCancel(task);
	}
	
	TaskQueue::~TaskQueue(){
		ICK_SCOPED_LOCK(mutex_);
		while(queue_.num() > 0){
			Cancel(queue_.first());
		}
	}
	
	Mutex * TaskQueue::mutex(){
		return & mutex_;
	}

	void TaskQueue::Post(Task * task){
		ICK_LOG_INFO("task queue post begin\n");
		ICK_SCOPED_LOCK(mutex_);
		queue_.InsertLast(task);
		mutex_.Broadcast();
		ICK_LOG_INFO("task queue post end\n");
	}
	void TaskQueue::Cancel(Task * task){
		ICK_SCOPED_LOCK(mutex_);
		// タスクを探す
		LinkedListNode<Task *> * node = LinkedListFind(queue_, task);
		if(!node){ ICK_ABORT("task not found\n"); }
		Cancel(node);
	}

	Task * TaskQueue::Pick(){
//		ICK_SCOPED_LOCK(mutex_);
		while(true){
			LinkedListNode<Task *> * first = queue_.first();
			if(first){
				Task * task = first->value();
				queue_.Remove(first);
				return task;
			}
			ICK_LOG_INFO("task queue wait\n");
			mutex_.Wait();
			ICK_LOG_INFO("task queue awake\n");
		}
	}
}
