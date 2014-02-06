#pragma once

#include <jni.h>

namespace ick{
	namespace jni{
		namespace activity{
			void StaticInit(JNIEnv * env);
			void StaticRelease(JNIEnv * env);
		}
	}
}
