LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := IronCake

MY_SRC_DIR := ../../src

LOCAL_SRC_FILES := \
	$(MY_SRC_DIR)/ick/base/allocator.cpp \
	$(MY_SRC_DIR)/ick/base/debug_allocator.cpp \
	$(MY_SRC_DIR)/ick/base/memory.cpp \
	$(MY_SRC_DIR)/ick/base/cstr.cpp \
	$(MY_SRC_DIR)/ick/base/crt.cpp \
	$(MY_SRC_DIR)/ick/base/log.cpp

include $(BUILD_STATIC_LIBRARY)