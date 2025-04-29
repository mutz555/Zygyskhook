LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := fingerprint_bypass
LOCAL_SRC_FILES := hook.cpp
LOCAL_CPPFLAGS += -std=c++17 -Wall -Wextra
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)
