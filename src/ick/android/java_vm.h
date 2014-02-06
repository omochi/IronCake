#pragma once

#include <jni.h>

namespace ick{
	namespace jni{
		extern JavaVM * g_java_vm;
		
		// スレッド用のenvをVMから取ってくる
		JNIEnv * GetEnv();
	}
}
