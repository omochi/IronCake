#pragma once

#include "thread.h"
#include "task_queue.h"

//	終了する際は、PostQuit(), Join()

namespace ick{
	class TaskQueueThread : public Thread {
	private:
		TaskQueue task_queue_;

		bool do_quit_;
		
		void QuitTask(bool cancelled);
	public:
		TaskQueueThread();
		virtual ~TaskQueueThread();
		
		TaskQueue * task_queue();
		
		void Post(Task * task);
		void PostQuit();
		
		virtual void Run();
	};
}
