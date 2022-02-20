// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "gameAPK/PhotoGalleryInterface.h"
#include "MyHUD.generated.h"

class IPhotoLibrary;


/**
 * 
 */
UCLASS()
class GAMEAPK_API AMyHUD : public AHUD
{
	GENERATED_BODY()

	AMyHUD();

private:
	class IPhotoLibrary* PhotoLibrary;

public:


	UFUNCTION(BlueprintCallable)
	virtual void OpenGallery();

	UFUNCTION(BlueprintCallable)
	virtual void OnPhotoSelected(TArray<uint8> PhotoBytes);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnPhotoSelected(class UTexture2D* SelectedPhoto);


	class UTexture2D* LoadImageFromBytes(const TArray<uint8>& ImageBytes);
};
