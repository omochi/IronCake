#pragma once

#include "../base/linked_list.h"
#include "mutex.h"

#include "task.h"
#include "task_queue_interface.h"

namespace ick{
	class TaskQueue : public TaskQueueInterface {
	private:
		Mutex mutex_;
		LinkedList<Task *> queue_;
		
		void Cancel(LinkedListNode<Task *> * task_node);
	public:
		// 残っているタスクはキャンセルされる
		virtual ~TaskQueue();
		
		Mutex * mutex();
		
		virtual void Post(Task * task);
		virtual void Cancel(Task * task);

		// ロックしてから呼び出して、
		// アンロックまでに実行、解放すること。
		// そうしなければ、Cancelでバグる。
		Task * Pick();
	};
}

