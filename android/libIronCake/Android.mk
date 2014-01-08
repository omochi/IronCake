LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := IronCake

MY_SRC_DIR := ../../src

LOCAL_SRC_FILES := \
	$(MY_SRC_DIR)/ick/base/allocator.cpp \
	$(MY_SRC_DIR)/ick/base/debug_allocator.cpp

include $(BUILD_STATIC_LIBRARY)