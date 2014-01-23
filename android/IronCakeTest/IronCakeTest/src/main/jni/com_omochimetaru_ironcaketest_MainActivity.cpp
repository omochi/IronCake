#include "com_omochimetaru_ironcaketest_MainActivity.h"

#include <iostream>
#include <gtest/gtest.h>
#include <android/log.h>

JNIEXPORT void JNICALL Java_com_omochimetaru_ironcaketest_MainActivity_doTest
(JNIEnv * env, jobject thiz){
	int argc = 0;
	char * argv[0] = {};
	
	testing::InitGoogleTest(&argc, argv);
	
	testing::internal::CaptureStdout();
	
	(void)testing::UnitTest::GetInstance()->Run();
	
	__android_log_write(ANDROID_LOG_INFO, "IronCake",
						testing::internal::GetCapturedStdout().c_str());

}

JNIEXPORT jint JNICALL Java_com_omochimetaru_ironcaketest_MainActivity_getTotalTestCaseCount
(JNIEnv * env, jobject thiz){
	testing::UnitTest * test = testing::UnitTest::GetInstance();
	return test->total_test_case_count();
}

JNIEXPORT jint JNICALL Java_com_omochimetaru_ironcaketest_MainActivity_getSuccessfulTestCaseCount
(JNIEnv * env, jobject thiz){
	testing::UnitTest * test = testing::UnitTest::GetInstance();
	return test->successful_test_case_count();
}

JNIEXPORT jint JNICALL Java_com_omochimetaru_ironcaketest_MainActivity_getFailedTestCaseCount
(JNIEnv * env, jobject thiz){
	testing::UnitTest * test = testing::UnitTest::GetInstance();
	return test->failed_test_case_count();
}

JNIEXPORT jint JNICALL Java_com_omochimetaru_ironcaketest_MainActivity_getTotalTestCount
(JNIEnv * env, jobject thiz){
	testing::UnitTest * test = testing::UnitTest::GetInstance();
	return test->total_test_count();
}

JNIEXPORT jint JNICALL Java_com_omochimetaru_ironcaketest_MainActivity_getSuccessfulTestCount
(JNIEnv * env, jobject thiz){
	testing::UnitTest * test = testing::UnitTest::GetInstance();
	return test->successful_test_count();
}

JNIEXPORT jint JNICALL Java_com_omochimetaru_ironcaketest_MainActivity_getFailedTestCount
(JNIEnv * env, jobject thiz){
	testing::UnitTest * test = testing::UnitTest::GetInstance();
	return test->failed_test_count();
}
