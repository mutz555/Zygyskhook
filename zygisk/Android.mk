LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := fingerprint_bypass
LOCAL_SRC_FILES := hook.cpp
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include
include $(BUILD_SHARED_LIBRARY)
