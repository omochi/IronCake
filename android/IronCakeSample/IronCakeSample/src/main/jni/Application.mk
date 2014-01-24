APP_BUILD_SCRIPT := $(NDK_PROJECT_PATH)/jni/Android.mk

APP_PLATFORM := android-14
APP_MODULES := IronCakeSample
NDK_TOOLCHAIN_VERSION := clang

APP_CFLAGS += -Wno-implicit-exception-spec-mismatch
