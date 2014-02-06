#include "startup.h"

#include "java_vm.h"
#include "activity.h"
#include "native_task.h"
#include "android_task_queue.h"

namespace ick{
	namespace jni{
		void Startup(JNIEnv * env){
			if(env->GetJavaVM(&java_vm) != JNI_OK){ ICK_ABORT("GetJavaVM failed\n"); }
			
			activity::StaticInit(env);
			native_task::StaticInit(env);
			AndroidTaskQueue::StaticInit(env);
		}
		void Shutdown(JNIEnv * env){
			activity::StaticRelease(env);
			native_task::StaticRelease(env);
			AndroidTaskQueue::StaticRelease(env);
		}
	}
}
