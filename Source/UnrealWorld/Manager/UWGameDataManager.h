// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnrealWorld/Manager/UWManagerBase.h"
#include "UWGameDataManager.generated.h"

/**
 * 
 */


UCLASS()
class UNREALWORLD_API UUWGameDataManager : public UUWManagerBase
{
	GENERATED_BODY()
	
public:
	// Inherited via UUWManagerBase
	virtual void Init() override;
	virtual void Tick(float InDeltaTime) override;
	virtual void Release() override;
};
