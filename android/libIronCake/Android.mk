LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := IronCake

LOCAL_SRC_FILES := \
	../../src/ick/base/allocator.cpp

include $(BUILD_STATIC_LIBRARY)