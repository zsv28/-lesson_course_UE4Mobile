#pragma once

#include "CoreMinimal.h"
#include "PhotoGalleryInterface.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif

DECLARE_DELEGATE_OneParam(FOnImageSelectedFromGallery, TArray<uint8>)

#define DECLARE_JAVA_METHOD(name) static jmethodID name;

class AndroidPhotoLibrary : public IPhotoLibrary
{

#if PLATFORM_ANDROID
public:
	static struct _JNIEnv* ENV;

	DECLARE_JAVA_METHOD(AndroidThunkJava_OpenGallery);

	JNIEXPORT void Java_com_epicgames_ue4_GameActivity_onImageSelected(JNIEnv* jni, jclass clazz, jbyteArray imageBytes)
	{
		AsyncTask(ENamedThreads::GameThread, [=]()
			{
				if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
				{
					jbyte* dataPtr = Env->GetByteArrayElements(imageBytes, NULL);
					jsize len = Env->GetArrayLength(imageBytes);
					TArray<uint8> result((uint8*)dataPtr, (int32)len);
					ImageSelectedFromGalleryProxy.ExecuteIfBound(result);
				}
			}
		);
	}
#define INIT_JAVA_METHOD(name, signature) \
if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true)) { \
	name = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, #name, signature, false); \
	check(name != NULL); \
} else { \
	check(0); \
}
#endif

public:
	AndroidPhotoLibrary();
	virtual void OpenGallery() override;
	static FOnImageSelectedFromGallery ImageSelectedFromGalleryProxy;
};

