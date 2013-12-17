#include "thread.h"

#include "../base/memory.h"
#include "../base/error.h"

#include <pthread.h>

namespace ick{
	struct ThreadImpl{
		pthread_t thread;
	};
	Thread::Thread():running_(false){
		impl_ = ICK_NEW0(ThreadImpl);
	}
	Thread::~Thread(){
		if(running_){ ICK_ABORT("still running"); }
		ICK_DELETE(impl_);
	}
	
	static void * ThreadRun(void * context) {
		Thread * thread;
		thread = static_cast<Thread *>(context);
		thread->Run();
		return NULL;
	}
	
	void Thread::Start(){
		if(running_){ ICK_ABORT("already running"); }
		running_ = true;
		ICK_EN_CALL(pthread_create(&impl_->thread, NULL, &ThreadRun, this));
	}
	void Thread::Join(){
		if(running_){
			running_ = false;
			ICK_EN_CALL(pthread_join(impl_->thread, NULL));
		}
	}
}

