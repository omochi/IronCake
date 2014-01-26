#pragma once

#include <jni.h>

namespace ick{
	namespace jni{
		extern jmethodID activity_controller_construct_method;
		extern jmethodID activity_schedule_update_timer_method;
		extern jfieldID activity_application_field;
		
		extern jmethodID surface_holder_get_surface_method;
	}
}
