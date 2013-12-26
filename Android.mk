LOCAL_PATH:=$(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libmonkeysaudio

LOCAL_SRC_FILES += \
	MACLib/APECompressCore.cpp \
	MACLib/APECompress.cpp \
	MACLib/APECompressCreate.cpp \
	MACLib/APEDecompress.cpp \
	MACLib/APEHeader.cpp \
	MACLib/APEInfo.cpp \
	MACLib/APELink.cpp \
	MACLib/APESimple.cpp \
	MACLib/APETag.cpp \
	MACLib/BitArray.cpp \
	MACLib/MACLib.cpp \
	MACLib/MACProgressHelper.cpp \
	MACLib/md5.cpp \
	MACLib/NewPredictor.cpp \
	MACLib/NNFilter.cpp \
	MACLib/Prepare.cpp \
	MACLib/UnBitArrayBase.cpp \
	MACLib/UnBitArray.cpp \
	MACLib/WAVInputSource.cpp \
	Shared/CharacterHelper.cpp \
	Shared/CircleBuffer.cpp \
	Shared/GlobalFunctions.cpp \
	Shared/StdLibFileIO.cpp \
	Shared/WinFileIO.cpp 

LOCAL_C_INCLUDES += \
	external/libmonkeysaudio/MACLib \
	external/libmonkeysaudio/Shared

LOCAL_CPPFLAGS += -fexceptions -fpermissive
LOCAL_LDFLAGS += -L$(ANDROID_BUILD_TOP)/prebuilts/ndk/8/sources/cxx-stl/gnu-libstdc++/libs/armeabi-v7a/ -lsupc++
LOCAL_LDFLAGS += -llog
include $(BUILD_SHARED_LIBRARY)
