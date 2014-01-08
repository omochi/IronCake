LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := IronCake

MY_SRC_DIR := ../../src

LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/allocator.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/debug_allocator.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/memory.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/cstr.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/crt.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/log.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/abort.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/assert.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/linked_list.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/array.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/string.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/math.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/error.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/time.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/property.cpp

include $(BUILD_STATIC_LIBRARY)