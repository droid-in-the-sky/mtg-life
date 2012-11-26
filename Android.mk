LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH       := android-project/jni/SDL
SDL_image_PATH := android-project/jni/SDL_image
SDL_ttf_PATH   := android-project/jni/SDL_ttf
SDL_mixer_PATH := android-project/jni/SDL_mixer

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
                    $(LOCAL_PATH)/$(SDL_image_PATH)   \
		    $(LOCAL_PATH)/$(SDL_ttf_PATH)     \
		    $(LOCAL_PATH)/$(SDL_mixer_PATH)

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.cpp \
	main.c

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_ttf SDL2_mixer

LOCAL_LDLIBS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)

$(shell (cd $(LOCAL_PATH) ; ceu --m4 --tp-word 4 --tp-pointer 4 mtg_life.ceu))
