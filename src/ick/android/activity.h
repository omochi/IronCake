#pragma once

#include <jni.h>

namespace ick{
	namespace jni{
		namespace activity{
			extern jmethodID controller_construct_method;
			extern jmethodID schedule_update_timer_method;
			extern jfieldID application_field;
			
			extern jmethodID surface_holder_get_surface_method;
		}
	}
}
