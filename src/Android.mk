LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)




LOCAL_SRC_FILES := main.c
LOCAL_CFLAGS := -Wall -Werror
LOCAL_MODULE:= tvd
LOCAL_MODULE_PATH := $(TARGET_OUT_EXECUTABLES)
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)