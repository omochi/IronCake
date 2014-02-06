#pragma once

#include <jni.h>

namespace ick{
	namespace jni{
		void Startup(JNIEnv * env);
		void Shutdown(JNIEnv * env);
	}
}
