#pragma once

#include <jni.h>

namespace ick{
	namespace jni{
		void AttachCurrentThread(JavaVM * vm);
		void DetachCurrentThread(JavaVM * vm);
	}
}
