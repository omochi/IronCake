LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := IronCakeTest

MY_SRC_DIR := ../../test

LOCAL_CFLAGS += -Wall
LOCAL_CPPFLAGS += -std=gnu++11

LOCAL_SRC_FILES += $(MY_SRC_DIR)/allocator_test.cpp

LOCAL_STATIC_LIBRARIES += IronCake
LOCAL_STATIC_LIBRARIES += gtest

include $(BUILD_SHARED_LIBRARY)

include ../IronCake/Android.mk
include ../gtest/Android.mk
