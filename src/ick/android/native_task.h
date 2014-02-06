#pragma once

#include <jni.h>
#include "../function/function_macro.h"

namespace ick{
	namespace jni{
		namespace native_task{
			typedef ICK_FUNCTION(void, JNIEnv *, jobject) NativeFunction;
			
			void StaticInit(JNIEnv * env);
			void StaticRelease(JNIEnv * env);
			
			NativeFunction * GetNativeFunction(JNIEnv * env, jobject task);
			void SetNativeFunction(JNIEnv * env, jobject task, NativeFunction * function);
									
			jobject Create(JNIEnv * env, const NativeFunction & function);
			void Release(JNIEnv * env, jobject task);
			
			void Run(JNIEnv * env, jobject task);			
		}
	}
}



