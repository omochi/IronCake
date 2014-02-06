#include "task_queue_thread.h"

#include "scoped_lock.h"
#include "../function/function_bind.h"

#ifdef ICK_ANDROID
#	include <jni.h>
#	include "../android/java_vm.h"
#endif

namespace ick{
	void TaskQueueThread::QuitTask(bool cancelled){
		(void)cancelled;
		do_quit_ = true;
	}
	
	TaskQueueThread::TaskQueueThread():
	do_quit_(false){
		
	}
	TaskQueueThread::~TaskQueueThread(){
		
	}
	TaskQueue * TaskQueueThread::task_queue(){
		return & task_queue_;
	}
	
	void TaskQueueThread::Run(){
#ifdef ICK_ANDROID
		JNIEnv * env = jni::GetEnv();
#endif
		while(!do_quit_){
#ifdef ICK_ANDROID
			if(env->PushLocalFrame(512)!=JNI_OK){ ICK_ABORT("PushLocalFrame failed\n"); }
#endif
			task_queue_.mutex()->Lock();
			TaskRun(task_queue_.Pick());
			task_queue_.mutex()->Unlock();
			
#ifdef ICK_ANDROID
			env->PopLocalFrame(NULL);
#endif
		}
	}

	void TaskQueueThread::Post(Task * task){
		task_queue_.Post(task);
	}
	
	void TaskQueueThread::PostQuit(){
		Post(TaskCreate(FunctionBind(&TaskQueueThread::QuitTask, this)));
	}
	
	
}
