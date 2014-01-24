MY_DIR := $(call my-dir)
LOCAL_PATH := .
include $(CLEAR_VARS)

LOCAL_MODULE := IronCakeSample

MY_IRONCAKE_ROOT_DIR := $(MY_DIR)/../../../../../..
MY_SRC_DIR := $(MY_IRONCAKE_ROOT_DIR)/sample

LOCAL_CFLAGS += -Wall
LOCAL_CPPFLAGS += -std=gnu++11

LOCAL_LDLIBS += -llog

LOCAL_SRC_FILES += $(MY_DIR)/main.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/sample_app_controller.cpp

LOCAL_SHARED_LIBRARIES += IronCake

include $(BUILD_SHARED_LIBRARY)

include $(MY_IRONCAKE_ROOT_DIR)/android/IronCake-mk/Android.mk
