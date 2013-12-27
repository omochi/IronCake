#pragma once

#include "../base/linked_list.h"
#include "../function/function.h"
#include "mutex.h"
#include "thread.h"

//	終了する際は、PostQuit(), Join()

namespace ick{
	class LoopThread : public Thread {
	private:
		Mutex mutex_;
		LinkedList<Function<void (*)()> > task_queue_;
		bool do_quit_;
		
		//強制キャンセルが入る余地を残す
		bool PickTask(Function<void (*)()> * task);
		
		friend void LoopThreadQuit(LoopThread * thiz);
	public:
		LoopThread();
		virtual ~LoopThread();
		
		virtual void Run();
		
		void Post(const Function<void (*)()> & task);

		void PostQuit();

	};
}
