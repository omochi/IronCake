#include "mutex.h"

#include "../base/memory.h"
#include "../base/error.h"

#ifdef ICK_WINDOWS
#	include <Windows.h>
#	include <process.h>
#	include "../windows/error.h"
#else
#	include <pthread.h>
#endif

namespace ick{
	struct MutexImpl{
#ifdef ICK_WINDOWS
		HANDLE mutex;
		HANDLE event;
#else
		pthread_mutex_t mutex;
		pthread_cond_t cond;
#endif
	};
	
	Mutex::Mutex():allocator_(static_allocator()){
		Init();
	}
	Mutex::Mutex(Allocator * allocator):allocator_(allocator){
		Init();
	}
	
	void Mutex::Init(){
		impl_ = ICK_NEW_A(allocator_, MutexImpl);
#ifdef ICK_WINDOWS
		impl_->mutex = CreateMutex(NULL, FALSE, NULL);
		if (!impl_->mutex){
			ICK_ABORT("CreateMutex: %s",WindowsLastErrorGetDescription().cstr());
		}
		impl_->event = CreateEvent(NULL, TRUE, FALSE, NULL);
		if (!impl_->event){
			ICK_ABORT("CreateEvent: %s",WindowsLastErrorGetDescription().cstr());
		}
#else
		impl_->mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;
		impl_->cond = PTHREAD_COND_INITIALIZER;
#endif
	}
	
	Mutex::~Mutex(){
#ifdef ICK_WINDOWS
		if (!CloseHandle(impl_->mutex)){
			ICK_ABORT("CloseHandle(mutex): %s",WindowsLastErrorGetDescription().cstr());
		}
		if (!CloseHandle(impl_->event)){
			ICK_ABORT("CloseHandle(event): %s", WindowsLastErrorGetDescription().cstr());
		}
#else
		ICK_EN_CALL(pthread_cond_destroy(&impl_->cond));
		ICK_EN_CALL(pthread_mutex_destroy(&impl_->mutex));
#endif

		ICK_DELETE_A(allocator_, impl_);
	}
	
	void Mutex::Lock(){
#ifdef ICK_WINDOWS
		DWORD ret = WaitForSingleObject(impl_->mutex, INFINITE);
		if(ret != WAIT_OBJECT_0){
			ICK_ABORT("%s", WindowsWaitResultGetDescription(ret).cstr());
		}
#else
		ICK_EN_CALL(pthread_mutex_lock(&impl_->mutex));
#endif
	}
	
	void Mutex::Unlock(){
#ifdef ICK_WINDOWS
		if (!ReleaseMutex(impl_->mutex)){
			ICK_ABORT("ReleaseMutex: %s",WindowsLastErrorGetDescription().cstr());
		}
#else
		ICK_EN_CALL(pthread_mutex_unlock(&impl_->mutex));
#endif
	}
	
	void Mutex::Wait(){
#ifdef ICK_WINDOWS
		DWORD ret = SignalObjectAndWait(impl_->mutex, impl_->event, INFINITE, FALSE);
		if (ret != WAIT_OBJECT_0){
			ICK_ABORT("%s", WindowsWaitResultGetDescription(ret).cstr());
		}
		ret = WaitForSingleObject(impl_->mutex, INFINITE);
		if(ret != WAIT_OBJECT_0){
			ICK_ABORT("%s", WindowsWaitResultGetDescription(ret).cstr());
		}
#else
		ICK_EN_CALL(pthread_cond_wait(&impl_->cond, &impl_->mutex));
#endif
	}
	
	void Mutex::Notify(){
#ifdef ICK_WINDOWS
		if (!SetEvent(impl_->event)){
			ICK_ABORT("SetEvent: %s",WindowsLastErrorGetDescription().cstr());
		}
		if (!ResetEvent(impl_->event)){
			ICK_ABORT("ResetEvent: %s", WindowsLastErrorGetDescription().cstr());
		}
#else
		ICK_EN_CALL(pthread_cond_broadcast(&impl_->cond));
#endif
	}
}
