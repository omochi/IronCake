MY_DIR := $(call my-dir)
LOCAL_PATH := .
include $(CLEAR_VARS)

LOCAL_MODULE := IronCake

MY_IRONCAKE_ROOT_DIR := $(MY_DIR)/../../../../../..
MY_SRC_DIR := $(MY_IRONCAKE_ROOT_DIR)/src

LOCAL_CFLAGS += -Wall
LOCAL_CPPFLAGS += -std=gnu++11

LOCAL_EXPORT_C_INCLUDES += $(MY_SRC_DIR)

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

LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/function/function.cpp

LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/thread/mutex.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/thread/scoped_lock.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/thread/thread.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/thread/function_thread.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/thread/loop_thread.cpp

LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/ick.cpp

include $(BUILD_STATIC_LIBRARY)
