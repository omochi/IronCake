#include <jni.h>

#include "../../../../../../sample/sample_app_controller.h"

#ifdef __cplusplus
extern "C" {
#endif

	jint JNI_OnLoad(JavaVM *vm, void *reserved){
		ick::g_startup_config.memory_debug = true;
		return JNI_VERSION_1_6;
	}
	
	JNIEXPORT jlong JNICALL Java_com_omochimetaru_ironcakesample_MainActivity_controllerConstruct
	(JNIEnv * env, jobject thiz){
		return reinterpret_cast<jlong>(ICK_NEW(SampleAppController));
	}

#ifdef __cplusplus
}
#endif