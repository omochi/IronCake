#pragma once

#include <jni.h>

namespace ick{
	template <typename FP> class Function;
	
	namespace jni{
		extern jclass native_task_class;
		
		namespace native_task{
			extern jmethodID constructor;
			extern jfieldID function_field;
			
			typedef ick::Function<void (*)(JNIEnv *,jobject)> NativeFunction;
			
			void StaticInit(JNIEnv * env);
			
			NativeFunction * GetNativeFunction(JNIEnv * env, jobject task);
			void SetNativeFunction(JNIEnv * env, jobject task, NativeFunction * function);
						
			jobject Create(JNIEnv * env, const NativeFunction & function);
			void Release(JNIEnv * env, jobject task);
			
			void Run(JNIEnv * env, jobject task);
			
		}
	}
}
