MY_DIR := $(call my-dir)
LOCAL_PATH := .
include $(CLEAR_VARS)

LOCAL_MODULE := gtest

MY_BASE_DIR := $(MY_DIR)/../../libs/googletest

LOCAL_CPPFLAGS += -std=gnu++11

LOCAL_CPP_EXTENSION := .cc

LOCAL_C_INCLUDES += $(MY_BASE_DIR)
LOCAL_C_INCLUDES += $(MY_BASE_DIR)/include
LOCAL_SRC_FILES += $(MY_BASE_DIR)/src/gtest-all.cc

LOCAL_EXPORT_C_INCLUDES += $(MY_BASE_DIR)/include
LOCAL_EXPORT_LDLIBS += -llog

include $(BUILD_STATIC_LIBRARY)
