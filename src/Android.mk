LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= dvb_t.c \
                  io.c \
                  main.c \
                  pdu.c \
                  pdubuf.c \
                  registry.c \
                  service.c \
                  thread.c
LOCAL_C_INCLUDES := system/libfdio/include
LOCAL_CFLAGS := -DANDROID_VERSION=$(PLATFORM_SDK_VERSION) -Wall -Werror
LOCAL_SHARED_LIBRARIES := libfdio \
                          libhardware \
                          libhardware_legacy \
                          liblog
LOCAL_MODULE:= tvd
LOCAL_MODULE_PATH := $(TARGET_OUT_EXECUTABLES)
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)
