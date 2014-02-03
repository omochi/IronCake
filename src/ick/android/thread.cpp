#include "thread.h"

#include "../base/abort.h"

namespace ick{
	namespace jni{
		void AttachCurrentThread(JavaVM * vm){
			JNIEnv * env;
			if(vm->AttachCurrentThread(&env, NULL) != JNI_OK){
				ICK_ABORT("AttachCurrentThread failed\n");
			}
		}
		void DetachCurrentThread(JavaVM * vm){
			if(vm->DetachCurrentThread() != JNI_OK){
				ICK_ABORT("DetachCurrentThread failed\n");
			}
		}
	}
}
