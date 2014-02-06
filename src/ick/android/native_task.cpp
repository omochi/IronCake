#include "native_task.h"

#include "../base/log.h"
#include "../function/function.h"

namespace ick{
	namespace jni{
		jclass native_task_class = NULL;
		
		namespace native_task{
			jmethodID constructor;
			jfieldID function_field;
			jfieldID auto_release_field;
			
			void StaticInit(JNIEnv * env){
				if(!native_task_class){
					ICK_LOG_INFO("NativeTask StaticInit\n");
					native_task_class = static_cast<jclass>(env->NewGlobalRef(env->FindClass("com/omochimetaru/ironcake/NativeTask")));
					constructor = env->GetMethodID(native_task_class, "<init>", "()V");
					function_field = env->GetFieldID(native_task_class, "function", "J");
					auto_release_field = env->GetFieldID(native_task_class, "autoRelease", "Z");
				}
			}
			
			NativeFunction * GetNativeFunction(JNIEnv * env, jobject task){
				return reinterpret_cast<NativeFunction *>(env->GetLongField(task, function_field));
			}
			
			void SetNativeFunction(JNIEnv * env, jobject task, NativeFunction * function){
				env->SetLongField(task, function_field, reinterpret_cast<jlong>(function));
			}
			
			bool GetAutoRelease(JNIEnv * env, jobject task){
				return static_cast<bool>(env->GetBooleanField(task, auto_release_field));
			}
			void SetAutoRelease(JNIEnv * env, jobject task, bool auto_release){
				env->SetBooleanField(task, auto_release_field, static_cast<jboolean>(auto_release));
			}
			
			jobject Create(JNIEnv * env, const NativeFunction & function, bool auto_release){
				StaticInit(env);
				jobject task = env->NewObject(native_task_class, constructor);
				SetNativeFunction(env, task, ICK_NEW(NativeFunction, function));
				SetAutoRelease(env, task, auto_release);
				return task;
			}
			void Release(JNIEnv * env, jobject task){
				NativeFunction * function = GetNativeFunction(env, task);
				if(function){
					ICK_DELETE(function);
					SetNativeFunction(env, task, NULL);
				}
			}
			void Run(JNIEnv * env, jobject task){
				NativeFunction * function = GetNativeFunction(env, task);
				if(function){
					(*function)(env, task);
				}
				if(GetAutoRelease(env, task)){
					Release(env, task);
				}
			}
		}
	}
}

#ifdef __cplusplus
extern "C" {
#endif
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_NativeTask_nativeStaticInit
	(JNIEnv * env, jclass clazz){
		ick::jni::native_task::StaticInit(env);
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_NativeTask_run
	(JNIEnv * env, jobject thiz){
		ick::jni::native_task::Run(env, thiz);
	}
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcake_NativeTask_release
	(JNIEnv * env, jobject thiz){
		ick::jni::native_task::Release(env, thiz);
	}
	
#ifdef __cplusplus
}
#endif

