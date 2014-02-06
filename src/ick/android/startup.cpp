#include "startup.h"

#include "java_vm.h"
#include "native_task.h"
#include "android_task_queue.h"

namespace ick{
	namespace jni{
		void Startup(JNIEnv * env){
			if(env->GetJavaVM(&java_vm) != JNI_OK){ ICK_ABORT("GetJavaVM failed\n"); }
			
			native_task::StaticInit(env);
			AndroidTaskQueue::StaticInit(env);
		}
		void Shutdown(JNIEnv * env){
			native_task::StaticRelease(env);
			AndroidTaskQueue::StaticRelease(env);
		}
	}
}
