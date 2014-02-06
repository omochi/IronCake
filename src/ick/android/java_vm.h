#pragma once

#include <jni.h>

namespace ick{
	class Mutex;
	
	namespace jni{
		extern JavaVM * java_vm;
		
		// スレッド用のenvをVMから取ってくる
		JNIEnv * GetEnv();
	}
}
