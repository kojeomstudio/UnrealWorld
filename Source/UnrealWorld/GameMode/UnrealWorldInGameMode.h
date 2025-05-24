// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Modules/ModuleManager.h"
#include "UnrealWorldInGameMode.generated.h"

class UUWGameCameraManager;
class APlayerGameCameraActor;
class AActor;
class APlayerStart;
/**
 * 
 */
UCLASS()
class UNREALWORLD_API AUnrealWorldInGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);

public:
	
protected:
	virtual void StartPlay();

protected:
	//UPROPERTY(Category = InGameProperty, EditAnywhere)
	//APlayerStart* StartTarget;
};
