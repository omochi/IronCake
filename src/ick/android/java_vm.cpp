#include "thread.h"

#include "../base/abort.h"

namespace ick{
	namespace jni{
		JavaVM * g_java_vm = NULL;
		
		JNIEnv * GetEnv(){
			JNIEnv * env;
			if(g_java_vm->GetEnv(reinterpret_cast<void**>(&env),
								 JNI_VERSION_1_6) != JNI_OK){
				ICK_ABORT("GetEnv failed\n");
			}
			return env;
		}
	}
}
