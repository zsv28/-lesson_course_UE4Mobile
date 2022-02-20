// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include <IImageWrapper.h>
#include "IImageWrapperModule.h"
#include "AndroidPhotoLibrary.h"

AMyHUD::AMyHUD()
{
#if PLATFORM_ANDROID     
	PhotoLibrary = new AndroidPhotoLibrary();
#endif
}

void AMyHUD::OpenGallery()
{
	if (PhotoLibrary)
	{
		PhotoLibrary->OnImageSelected.BindUObject(this, &AMyHUD::OnPhotoSelected);
		PhotoLibrary->OpenGallery();

	}
}

void AMyHUD::OnPhotoSelected(TArray<uint8> PhotoBytes)
{
	int32 len = PhotoBytes.Num();
	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			UTexture2D* ImportedTexture = LoadImageFromBytes(PhotoBytes);
			BP_OnPhotoSelected(ImportedTexture);
		});
}

class UTexture2D* AMyHUD::LoadImageFromBytes(const TArray<uint8>& ImageBytes)
{
	auto& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	EImageFormat ImageFormat = ImageWrapperModule.DetectImageFormat(ImageBytes.GetData(), ImageBytes.Num());
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);

	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(ImageBytes.GetData(), ImageBytes.Num()))
	{
		TArray<uint8> UncompressedBGRA;
		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			FName UniqueName = MakeUniqueObjectName(nullptr, UTexture2D::StaticClass());
			UTexture2D* NewTexture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), EPixelFormat::PF_B8G8R8A8, UniqueName);

			if (!NewTexture) return nullptr;
			if (UTexture2D* ImageTexture = Cast<UTexture2D>(NewTexture))
			{
				void* TextureData = ImageTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);//locking the data its multithreaded
				FMemory::Memmove(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
				//FMemory::Memzero((void *)PixelData.GetData(), PixelData.Num() * sizeof(uint8));
				ImageTexture->PlatformData->Mips[0].BulkData.Unlock();
				ImageTexture->UpdateResource();
			}

			return NewTexture;
		}
	}

	return nullptr;

}
