#include "android_task_queue.h"


#include "../thread/scoped_lock.h"
#include "../function/function_bind.h"

#include "java_vm.h"
#include "native_task.h"


namespace ick{
	static jmethodID handler_post_method = NULL;
	
	void AndroidTaskQueue::StaticInit(JNIEnv * env){
		jclass handler_class = env->FindClass("android/os/Handler");
		handler_post_method = env->GetMethodID(handler_class, "post", "(Ljava/lang/Runnable;)Z");
	}
	
	void AndroidTaskQueue::StaticRelease(JNIEnv * env){
	}
	
	AndroidTaskQueue::AndroidTaskQueue(JNIEnv * env){
		// 現在のスレッドのHandlerを取得する
		
		jclass looper_class = env->FindClass("android/os/Looper");
		jmethodID my_looper_method = env->GetStaticMethodID(looper_class, "myLooper", "()Landroid/os/Looper;");
		jobject current_looper = env->CallStaticObjectMethod(looper_class, my_looper_method);
		if(!current_looper){ ICK_ABORT("not android looper thread\n"); }
		
		jclass handler_class = env->FindClass("android/os/Handler");
		jmethodID handler_ctor = env->GetMethodID(handler_class, "<init>", "(Landroid/os/Looper;)V");

		handler_ = env->NewGlobalRef(env->NewObject(handler_class, handler_ctor, current_looper));
	}
	AndroidTaskQueue::~AndroidTaskQueue(){
		ICK_SCOPED_LOCK(mutex_);
		JNIEnv * env = jni::GetEnv();

		// 残余タスクの解放
		ICK_LOG_INFO("cancel task num: %d\n",shadow_queue_.num());
		while(shadow_queue_.num() > 0){
			Cancel(env, shadow_queue_.first());
		}
		
		env->DeleteGlobalRef(handler_);
	}
	
	void AndroidTaskQueue::Post(Task * task){
		ICK_SCOPED_LOCK(mutex_);
		// Post元スレッドのenv
		JNIEnv * env = jni::GetEnv();
		
		jobject java_task = jni::native_task::Create(env,
													 FunctionBind(&AndroidTaskQueue::JavaTaskRun,
																  this));
		QueueItem queue_item = { env->NewGlobalRef(java_task), task };
		shadow_queue_.InsertLast(queue_item);
		
		if(!env->CallBooleanMethod(handler_, handler_post_method, java_task)){
			ICK_ABORT("Handler post failed\n");
		}
	}
	
	// TaskRun
	void AndroidTaskQueue::JavaTaskRun(JNIEnv * env, jobject java_task){
		ICK_SCOPED_LOCK(mutex_);
		LinkedListNode<QueueItem> * node = shadow_queue_.first();
		QueueItem queue_item = node->value();
		
		// 一致してるかチェックする
		if(!env->IsSameObject(queue_item.java_task, java_task)){
			ICK_ABORT("invalid java task\n");
		}
		TaskRun(queue_item.user_task);
		ReleaseQueueItem(env, shadow_queue_.first());
	}
	
	// TaskCancel
	void AndroidTaskQueue::Cancel(Task * task){
		ICK_SCOPED_LOCK(mutex_);
		// タスクを探す
		LinkedListNode<QueueItem> * found_node = NULL;
		for(LinkedListNode<QueueItem> * node = shadow_queue_.first(); node != NULL; node = node->next()){
			if(node->value().user_task == task){
				found_node = node;
				break;
			}
		}
		if(!found_node){ ICK_ABORT("task not found\n"); }
		Cancel(jni::GetEnv(), found_node);
	}
	
	// TaskCancel
	void AndroidTaskQueue::Cancel(JNIEnv * env, LinkedListNode<QueueItem> * node){
		QueueItem queue_item = node->value();
		TaskCancel(queue_item.user_task);
		ReleaseQueueItem(env, node);
	}
	
	void AndroidTaskQueue::ReleaseQueueItem(JNIEnv * env, LinkedListNode<QueueItem> * node){
		QueueItem queue_item = node->value();
		shadow_queue_.Remove(node);
		jni::native_task::Release(env, queue_item.java_task);
		env->DeleteGlobalRef(queue_item.java_task);
	}
		
}
