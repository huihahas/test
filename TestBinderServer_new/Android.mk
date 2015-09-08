LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := eng

LOCAL_SRC_FILES:= \
	TestBinderService.cpp \
	binderservice.c
	
LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils \
	libbinder \
	libandroid_runtime \
	libtestBinderClient \
	libui			

LOCAL_C_INCLUDES := \
    $(TOP)/frameworks/base/include/ \
    $(TOP)/frameworks/tv/include/ \

LOCAL_MODULE:= libTestBinderServer

LOCAL_PRELINK_MODULE := false

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := eng

LOCAL_SRC_FILES:= \
	main_testBinder.cpp \
	
LOCAL_SHARED_LIBRARIES := \
	libutils \
	libbinder \
	libandroid_runtime \
	libTestBinderServer \
	libui			

LOCAL_C_INCLUDES := \
    $(TOP)/frameworks/base/include/ \
    $(TOP)/frameworks/tv/include/ \

LOCAL_MODULE:= main_testBinder

LOCAL_PRELINK_MODULE := false

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := eng

LOCAL_SRC_FILES:= \
	testBinder.cpp \
	
LOCAL_SHARED_LIBRARIES := \
	libutils \
	libbinder \
	libandroid_runtime \
	libtestBinderClient \
	libui			

LOCAL_C_INCLUDES := \
    $(TOP)/frameworks/base/include/ \
    $(TOP)/frameworks/tv/include/ \

LOCAL_MODULE:= testBinder

LOCAL_PRELINK_MODULE := false

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := eng

LOCAL_SRC_FILES:= \
	C2C++BinderTest.c \
	testBinder.cpp \
	
LOCAL_SHARED_LIBRARIES := \
	libutils \
	libbinder \
	libandroid_runtime \
	libtestBinderClient \
	libui			\

	
LOCAL_C_INCLUDES := \
    $(TOP)/frameworks/base/include/ \
    $(TOP)/frameworks/tv/include/ \

LOCAL_MODULE:= c2c++binder

LOCAL_PRELINK_MODULE := false

include $(BUILD_EXECUTABLE)
