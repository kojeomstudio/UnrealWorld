// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealWorld/Data/UWGameDataAssetBase.h"
#include "UWGameConfigDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UNREALWORLD_API UUWGameConfigDataAsset : public UUWGameDataAssetBase
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere)
	int32 TestValue = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	int32 SomethingValue = 10.0f;

	UPROPERTY(EditDefaultsOnly, category="Camera")
	float PlayerCameraRotateSpeed = 1.0f;
};
