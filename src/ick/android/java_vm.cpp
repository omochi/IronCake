#include "java_vm.h"

#include "../base/abort.h"

namespace ick{
	namespace jni{
		JavaVM * java_vm = NULL;
		
		JNIEnv * GetEnv(){
			JNIEnv * env;
			if(java_vm->GetEnv(reinterpret_cast<void**>(&env),
								 JNI_VERSION_1_6) != JNI_OK){
				ICK_ABORT("GetEnv failed\n");
			}
			return env;
		}
	}
}
