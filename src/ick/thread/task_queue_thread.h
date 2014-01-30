#pragma once

#include "../base/linked_list.h"
#include "mutex.h"
#include "thread.h"
#include "task_postable.h"

//	終了する際は、PostQuit(), Join()

namespace ick{
	class TaskQueueThread : public Thread, public TaskPostable {
	private:
		Mutex mutex_;
		LinkedList<Function<void (*)()> > task_queue_;
		bool do_quit_;
		
		Function<void (*)()> PickTask();
		
		void Quit();
	public:
		TaskQueueThread();
		virtual ~TaskQueueThread();
		
		virtual void Run();
		
		void PostTask(const Function<void (*)()> & task);

		void PostQuit();

	};
}
