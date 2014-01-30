#pragma once

#include <jni.h>

#include "../base/linked_list.h"
#include "../function/function.h"
#include "../thread/mutex.h"
#include "../thread/task_postable.h"

#include "native_task.h"

// android.os.Handlerにポストする。
// ぶら下げたネイティブタスクのリストを持つので、
// 取り出し前の強制解放ができる。

// ポスト元はVMがアタッチされたスレッドで無いといけない

// newしたスレッドでdeleteすること

namespace ick{

	class AndroidHandler : public TaskPostable {
	private:
		static jmethodID handler_post_method_;
		static void StaticInit(JNIEnv * env);
		
		JavaVM * vm_;
		JNIEnv * env_;
		jobject handler_;
		
		Mutex mutex_;
		LinkedList<jobject> posting_tasks_;

	public:
		AndroidHandler(JNIEnv * env, jobject handler);
		virtual ~AndroidHandler();
		
		void PostTask(const Function<void (*)()> & task);
	private:
		void TaskRun(Function<void (*)()> user_task, JNIEnv * env, jobject task);
	};
}
