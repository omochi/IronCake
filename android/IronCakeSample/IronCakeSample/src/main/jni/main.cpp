#include <jni.h>

#include "../../../../../../sample/sample_app_controller.h"

#ifdef __cplusplus
extern "C" {
#endif

	JNIEXPORT jlong JNICALL Java_com_omochimetaru_ironcakesample_MainActivity_controllerConstruct
	(JNIEnv * env, jobject thiz){
		return reinterpret_cast<jlong>(ICK_NEW(SampleAppController));
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcakesample_MainActivity_willCreate
	(JNIEnv * env, jobject thiz){
		ick::g_startup_config.memory_debug = true;
	}
	
	JNIEXPORT void JNICALL Java_com_omochimetaru_ironcakesample_MainActivity_didDestroy
	(JNIEnv * env, jobject thiz){
	}
	

#ifdef __cplusplus
}
#endif