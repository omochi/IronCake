#pragma once

#include <jni.h>

#include "../base/linked_list.h"
#include "../thread/mutex.h"
#include "../thread/task_queue_interface.h"
#include "../function/function_macro.h"


// android.os.Handlerにポストする。
// 対応するハンドラはコンストラクタ時に、現在スレッドのものを自動取得する。

namespace ick{
	
	class AndroidTaskQueue : public TaskQueueInterface {
	private:
		struct QueueItem {
			jobject java_task;
			Task * user_task;
		};
		Mutex mutex_;
		jobject handler_;
		
		LinkedList<QueueItem> shadow_queue_;
	public:
		static void StaticInit(JNIEnv * env);
		static void StaticRelease(JNIEnv * env);
		
		AndroidTaskQueue(JNIEnv * env);
		virtual ~AndroidTaskQueue();
		
		virtual void Post(Task * task);
		virtual void Cancel(Task * task);
		
	private:
		void JavaTaskRun(JNIEnv * env, jobject java_task);
		
		void Cancel(JNIEnv * env, LinkedListNode<QueueItem> * node);
		void ReleaseQueueItem(JNIEnv * env, LinkedListNode<QueueItem> * node);
		
	};
}
