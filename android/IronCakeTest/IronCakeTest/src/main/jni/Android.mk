MY_DIR := $(call my-dir)
LOCAL_PATH := .
include $(CLEAR_VARS)

LOCAL_MODULE := IronCakeTest

MY_IRONCAKE_ROOT_DIR := $(MY_DIR)/../../../../../..
MY_SRC_DIR := $(MY_IRONCAKE_ROOT_DIR)/test

LOCAL_CFLAGS += -Wall
LOCAL_CPPFLAGS += -std=gnu++11

LOCAL_SRC_FILES += $(MY_DIR)/com_omochimetaru_ironcaketest_MainActivity.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/allocator_test.cpp

LOCAL_C_INCLUDES += $(MY_IRONCAKE_ROOT_DIR)/src
LOCAL_STATIC_LIBRARIES += IronCake
LOCAL_STATIC_LIBRARIES += gtest

include $(BUILD_SHARED_LIBRARY)

include $(MY_IRONCAKE_ROOT_DIR)/android/IronCake/Android.mk
include $(MY_IRONCAKE_ROOT_DIR)/android/gtest/Android.mk
