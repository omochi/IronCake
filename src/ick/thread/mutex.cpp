#include "mutex.h"

#include "../base/memory.h"
#include "../base/error.h"

#ifdef ICK_WINDOWS
#	include <Windows.h>
#	include <process.h>
#	include "../windows/error.h"
#	include "../windows/wait.h"
#else
#	include <pthread.h>
#endif

namespace ick{
	struct MutexImpl{
#ifdef ICK_WINDOWS
		CRITICAL_SECTION mutex_lock;

		int wait_count;
		CRITICAL_SECTION wait_count_lock;
		HANDLE signal_event;
		HANDLE broadcast_event;
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
		InitializeCriticalSection(&impl_->mutex_lock);
		impl_->wait_count = 0;
		InitializeCriticalSection(&impl_->wait_count_lock);
		impl_->signal_event = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (!impl_->signal_event){
			ICK_ABORT("CreateEvent: %s", WindowsLastErrorGetDescription().cstr());
		}
		impl_->broadcast_event = CreateEvent(NULL, TRUE, FALSE, NULL);
		if (!impl_->broadcast_event){
			ICK_ABORT("CreateEvent: %s", WindowsLastErrorGetDescription().cstr());
		}
#else
		impl_->mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;
		impl_->cond = PTHREAD_COND_INITIALIZER;
#endif
	}
	
	Mutex::~Mutex(){
#ifdef ICK_WINDOWS
		
		DeleteCriticalSection(&impl_->mutex_lock);
		DeleteCriticalSection(&impl_->wait_count_lock);
		if (!CloseHandle(impl_->signal_event)){
			ICK_ABORT("CloseHandle(signal_event): %s", WindowsLastErrorGetDescription().cstr());
		}
		if (!CloseHandle(impl_->broadcast_event)){
			ICK_ABORT("CloseHandle(broadcast_event): %s", WindowsLastErrorGetDescription().cstr());
		}
#else
		ICK_EN_CALL(pthread_cond_destroy(&impl_->cond));
		ICK_EN_CALL(pthread_mutex_destroy(&impl_->mutex));
#endif

		ICK_DELETE_A(allocator_, impl_);
	}
	
	void Mutex::Lock(){
#ifdef ICK_WINDOWS
		EnterCriticalSection(&impl_->mutex_lock);
#else
		ICK_EN_CALL(pthread_mutex_lock(&impl_->mutex));
#endif
	}
	
	void Mutex::Unlock(){
#ifdef ICK_WINDOWS
		LeaveCriticalSection(&impl_->mutex_lock);
#else
		ICK_EN_CALL(pthread_mutex_unlock(&impl_->mutex));
#endif
	}
	
	void Mutex::Wait(){
#ifdef ICK_WINDOWS
		EnterCriticalSection(&impl_->wait_count_lock);
		impl_->wait_count++;
		LeaveCriticalSection(&impl_->wait_count_lock);
		Unlock();

		HANDLE wait_events[] = { impl_->signal_event, impl_->broadcast_event };
		DWORD ret = WaitForMultipleObjects(ICK_ARRAY_SIZE(wait_events), wait_events, FALSE, INFINITE);
		int wait_object_index = WindowsWaitResultGetObjectIndex(ret, ICK_ARRAY_SIZE(wait_events));
		if (wait_object_index == -1){
			ICK_ABORT("Wait: %s", WindowsWaitResultGetDescription(ret, ICK_ARRAY_SIZE(wait_events)).cstr());
		}

		EnterCriticalSection(&impl_->wait_count_lock);
		impl_->wait_count--;
		if (impl_->wait_count == 0){
			if (!ResetEvent(impl_->broadcast_event)){
				ICK_ABORT("ResetEvent: %s", WindowsLastErrorGetDescription().cstr());
			}
		}
		LeaveCriticalSection(&impl_->wait_count_lock);

		Lock();
#else
		ICK_EN_CALL(pthread_cond_wait(&impl_->cond, &impl_->mutex));
#endif
	}
	
	void Mutex::Signal(){
#ifdef ICK_WINDOWS
		EnterCriticalSection(&impl_->wait_count_lock);
		if (impl_->wait_count > 0){
			if (!SetEvent(impl_->signal_event)){
				ICK_ABORT("SetEvent(signal_event): %s", WindowsLastErrorGetDescription().cstr());
			}
		}
		LeaveCriticalSection(&impl_->wait_count_lock);
#else
		ICK_EN_CALL(pthread_cond_signal(&impl_->cond));
#endif
	}

	void Mutex::Broadcast(){
#ifdef ICK_WINDOWS
		EnterCriticalSection(&impl_->wait_count_lock);
		if (impl_->wait_count > 0){
			if (!SetEvent(impl_->broadcast_event)){
				ICK_ABORT("SetEvent(broadcast_event): %s", WindowsLastErrorGetDescription().cstr());
			}
		}
		LeaveCriticalSection(&impl_->wait_count_lock);
#else
		ICK_EN_CALL(pthread_cond_broadcast(&impl_->cond));
#endif
	}
}
