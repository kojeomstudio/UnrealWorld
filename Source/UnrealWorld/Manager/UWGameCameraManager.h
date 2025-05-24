// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealWorld/Common/UWEnums.h"
#include "UObject/NoExportTypes.h"
#include "UnrealWorld/Manager/UWManagerBase.h"
#include "UWGameCameraManager.generated.h"

/**
 * 
 */

class APlayerGameCameraActor;

struct FGameCameraInitParams
{
public:
	FGameCameraInitParams() = default;
	FGameCameraInitParams(const FTransform& InSpawnTransform, TSubclassOf<class APlayerGameCameraActor> InTargetClass)
	: SpawnTransform(InSpawnTransform), CamActorClass(InTargetClass) 
	{
	}

	// getters.
public:
	const FTransform& GetSpawnTransform() const
	{
		return SpawnTransform;
	}

	TSubclassOf<class APlayerGameCameraActor> GetActorClass() const
	{
		return CamActorClass;
	}

private:
	FTransform SpawnTransform;
	TSubclassOf<class APlayerGameCameraActor> CamActorClass;
};

UCLASS()
class UNREALWORLD_API UUWGameCameraManager : public UUWManagerBase
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Tick(float InDeltaTime) override;
	virtual void Release() override;

	// getters.
public:
	const FVector GetCameraDirection() const;
	const FRotator GetCameraRotation() const;

public:
	void SpawnCamera(const FGameCameraInitParams& InInitParams);

private:
	UPROPERTY(Transient)
	APlayerGameCameraActor* PlayerCameraActor;
};
