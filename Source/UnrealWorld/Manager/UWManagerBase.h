// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealWorld/Common/UWEnums.h"
#include "UObject/NoExportTypes.h"
#include "UWManagerBase.generated.h"

/**
 * 
 */

UCLASS(Abstract)
class UNREALWORLD_API UUWManagerBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void Init() {}
	virtual void PostInit() {}
	virtual void Tick(float InDeltaTime) {}
	virtual void Release() {}

protected:
#if WITH_EDITOR
	void Test_Editor() {}
#endif
};
