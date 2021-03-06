MY_DIR := $(call my-dir)
LOCAL_PATH := .
include $(CLEAR_VARS)

LOCAL_MODULE := IronCake

MY_SRC_DIR := $(MY_DIR)/../../src

LOCAL_CFLAGS += -Wall
LOCAL_CPPFLAGS += -std=gnu++11

LOCAL_EXPORT_C_INCLUDES += $(MY_SRC_DIR)

LOCAL_LDLIBS += -llog
LOCAL_LDLIBS += -landroid
LOCAL_LDLIBS += -lEGL


LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/allocator.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/debug_allocator.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/memory.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/cstr.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/crt.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/log.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/abort.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/assert.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/string.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/math.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/error.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/time.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/base/property.cpp

LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/thread/mutex.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/thread/scoped_lock.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/thread/thread.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/thread/function_thread.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/thread/task.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/thread/task_queue.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/thread/task_queue_thread.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/thread/signal.cpp

LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/app/application.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/app/application_controller.cpp

LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/android/startup.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/android/java_vm.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/android/activity.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/android/native_task.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/android/android_task_queue.cpp

LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/ick.cpp
LOCAL_SRC_FILES += $(MY_SRC_DIR)/ick/startup.cpp

include $(BUILD_SHARED_LIBRARY)

