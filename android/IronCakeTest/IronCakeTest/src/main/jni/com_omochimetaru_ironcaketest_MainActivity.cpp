#include "com_omochimetaru_ironcaketest_MainActivity.h"

#include <ick/ick.h>

JNIEXPORT void JNICALL Java_com_omochimetaru_ironcaketest_MainActivity_doTest
(JNIEnv * env, jobject thiz){
	ICK_LOG_INFO("native method test");
}