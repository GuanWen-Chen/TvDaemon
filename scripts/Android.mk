LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := init.tv.rc
LOCAL_MODULE := init.tv.rc
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_ROOT_OUT)
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
