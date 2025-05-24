// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "UWGameIniConfig.generated.h"

// ref : https://dev.epicgames.com/documentation/en-us/unreal-engine/configuration-files-in-unreal-engine
//

UCLASS(Config=Game)
class UNREALWORLD_API UUWGameIniConfig : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Config)
	int32 DefaultRotatorX;

	UPROPERTY(Config)
	int32 DefaultRotatorY;
	
	UPROPERTY(Config)
	int32 DefaultRotatorZ;
};