#pragma once

#include <jni.h>

namespace ick{
	namespace jni{
		namespace activity{
			extern jmethodID controller_construct_method;
			extern jfieldID application_field;
			extern jfieldID main_thread_handler_field;
			
			extern jmethodID surface_holder_get_surface_method;
			
			extern jmethodID handler_post_delayed_method;
		}
	}
}

