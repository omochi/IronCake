#include "jni.h"

#include <android/log.h>
#include "../base/abort.h"

namespace ick{
	namespace jni{
		jmethodID activity_controller_construct_method;
		jmethodID activity_schedule_update_timer_method;
		jfieldID activity_application_field;
		
		jmethodID surface_holder_get_surface_method;
	}
}
