#include "thread.h"

#include "../base/memory.h"
#include "../base/abort.h"
#include "../base/error.h"

#ifdef ICK_WINDOWS
#	include <Windows.h>
#	include <process.h>
#	include "../windows/windows.h"
#else
#	include <pthread.h>
#endif

namespace ick{
	struct ThreadImpl{
#ifdef ICK_WINDOWS
		uintptr_t thread;
#else
		pthread_t thread;
#endif
	};

#ifdef ICK_WINDOWS
	static HANDLE ThreadImplGetHandle(ThreadImpl * impl){
		return reinterpret_cast<HANDLE>(impl->thread);
	}
#endif


	Thread::Thread():running_(false){
		impl_ = ICK_NEW(ThreadImpl);
	}
	Thread::~Thread(){
		if(running_){ ICK_ABORT("still running\n"); }
		ICK_DELETE(impl_);
	}
	
#ifdef ICK_WINDOWS
	static unsigned int __stdcall ThreadRun(void * context)  {
#else
	static void * ThreadRun(void * context) {
#endif
		Thread * thread;
		thread = static_cast<Thread *>(context);
		thread->Run();
#ifdef ICK_WINDOWS
		return 0;
#else
		return NULL;
#endif
	}


	void Thread::Start(){
		if(running_){ ICK_ABORT("already running\n"); }
		running_ = true;

#ifdef ICK_WINDOWS
		impl_->thread = _beginthreadex(NULL, 0, &ThreadRun, this, 0, NULL);
		if(!impl_->thread){
			ICK_EN_ABORT(errno, "_beginthreadex");
		}
#else
		ICK_EN_CALL(pthread_create(&impl_->thread, NULL, &ThreadRun, this));
#endif
	}
	void Thread::Join(){
		if (running_){
			running_ = false;
#ifdef ICK_WINDOWS
			DWORD wait_ret = WaitForSingleObject(ThreadImplGetHandle(impl_), INFINITE);
			if(wait_ret != WAIT_OBJECT_0){
				ICK_ABORT("%s",WindowsWaitResultGetDescription(wait_ret).cstr());
			}
			if (!CloseHandle(ThreadImplGetHandle(impl_))){
				ICK_ABORT("CloseHandle: %s", WindowsLastErrorGetDescription().cstr());
			}
#else
			ICK_EN_CALL(pthread_join(impl_->thread, NULL));
#endif
		}
	}
}

