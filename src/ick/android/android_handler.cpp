#include "android_handler.h"

#include "../thread/scoped_lock.h"
#include "../function/function_bind.h"

namespace ick{
	jmethodID AndroidHandler::handler_post_method_ = NULL;
	
	void AndroidHandler::StaticInit(JNIEnv * env){
		if(!handler_post_method_){
			jclass handler_class = env->FindClass("android/os/Handler");
			handler_post_method_ = env->GetMethodID(handler_class, "post", "(Ljava/lang/Runnable;)Z");
		}
	}
	
	AndroidHandler::AndroidHandler(JNIEnv * env, jobject handler){
		StaticInit(env);
		
		if(env->GetJavaVM(&vm_)){ ICK_ABORT("GetJavaVM failed\n"); }
		env_ = env;
		handler_ = env->NewGlobalRef(handler);
	}
	AndroidHandler::~AndroidHandler(){
		{
			ICK_SCOPED_LOCK(mutex_);
			//未実行タスクを解放しちゃう
			while(true){
				LinkedList<jobject>::Node * node = posting_tasks_.first();
				if(!node){ break; }
				jni::native_task::Release(env_, node->value());
				env_->DeleteGlobalRef(node->value());
				posting_tasks_.Remove(node);
			}
			
			ICK_LOG_INFO("posting_tasks_: %d\n",posting_tasks_.num());
		}
		env_->DeleteGlobalRef(handler_);
	}
	
	void AndroidHandler::PostTask(const Function<void (*)()> & task){
		//呼び出し元スレッドのenv
		JNIEnv * env;
		if(vm_->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK){
			ICK_ABORT("GetEnv failed\n");
		}
		//タスクを一段包む
		jobject java_task = jni::native_task::Create(env,
													 FunctionBind1(FunctionMake(this, &AndroidHandler::TaskRun), task),
													 true);
		
		{
			//未実行タスクリストに追加
			ICK_SCOPED_LOCK(mutex_);
			posting_tasks_.InsertLast(env->NewGlobalRef(java_task));
		}
		
		if(!env->CallBooleanMethod(handler_, handler_post_method_, java_task)){
			ICK_ABORT("Handler post failed\n");
		}
		
		env->DeleteLocalRef(java_task);
	}
	
	//抜けてくるとこちら
	void AndroidHandler::TaskRun(Function<void (*)()> user_task, JNIEnv * env, jobject task){
		{
			//未実行タスクリストから削除
			ICK_SCOPED_LOCK(mutex_);
			jobject posting_task = posting_tasks_.first()->value();
			posting_tasks_.Remove(posting_tasks_.first());
			
			//チェック
			if(!env->IsSameObject(posting_task, task)){
				ICK_ABORT("invalid task\n");
			}
			
			env->DeleteGlobalRef(posting_task);
		}
		user_task();
	}
	
}
