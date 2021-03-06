﻿#include "thread.h"

#include "../base/memory.h"
#include "../base/abort.h"
#include "../base/error.h"

#ifdef ICK_WINDOWS
#	include <Windows.h>
#	include <process.h>
#	include "../windows/error.h"
#	include "../windows/wait.h"
#else
#	include <pthread.h>
#endif

#ifdef ICK_ANDROID
#	include <jni.h>
#	include "../android/java_vm.h"
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

	Thread::Thread():
	running_(false),
	name_("ick::Thread"){
		impl_ = ICK_NEW(ThreadImpl);
	}
	Thread::~Thread(){
		if(running_){ ICK_ABORT("still running\n"); }
		ICK_DELETE(impl_);
	}
	
	ThreadImpl * Thread::impl() const{
		return impl_;
	}
	
	bool Thread::running() const{
		return running_;
	}
	String Thread::name() const{
		return name_;
	}
	void Thread::set_name(const String & name){
		name_ = name;
	}

#ifdef ICK_WINDOWS
	static unsigned int __stdcall ThreadRun(void * context)  {
#else
	static void * ThreadRun(void * context) {
#endif
		Thread * thiz = static_cast<Thread *>(context);
		
#ifdef ICK_WINDOWS
#elif defined ICK_MAC
		ICK_EN_CALL(pthread_setname_np(thiz->name().cstr()));
#else
		ICK_EN_CALL(pthread_setname_np(thiz->impl()->thread, thiz->name().cstr()));
#endif
		
#ifdef ICK_ANDROID
		JNIEnv * env;
		if(jni::java_vm->AttachCurrentThread(&env, NULL) != JNI_OK){
			ICK_ABORT("AttachCurrentThread failed\n");
		}
#endif
		thiz->Run();
#ifdef ICK_ANDROID
		if(jni::java_vm->DetachCurrentThread() != JNI_OK){
			ICK_ABORT("DetachCurrentThread failed\n");
		}
#endif
		
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
			ICK_EN_ABORT(errno, "_beginthreadex\n");
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
			if (WindowsWaitResultGetObjectIndex(wait_ret, 1) == -1){
				ICK_ABORT("Wait: %s\n",WindowsWaitResultGetDescription(wait_ret, 1).cstr());
			}
			if (!CloseHandle(ThreadImplGetHandle(impl_))){
				ICK_ABORT("CloseHandle: %s\n", WindowsLastErrorGetDescription().cstr());
			}
#else
			ICK_EN_CALL(pthread_join(impl_->thread, NULL));
#endif
		}
	}
}

