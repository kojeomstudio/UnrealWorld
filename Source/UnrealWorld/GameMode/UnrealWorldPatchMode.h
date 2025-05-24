// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Modules/ModuleManager.h"
#include "UnrealWorldPatchMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALWORLD_API AUnrealWorldPatchMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);

	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction);

public:
	UFUNCTION(BlueprintCallable)
	void CPP_DownloadPakFile(const FString& InUrl);

	UFUNCTION(BlueprintCallable)
	void CPP_DownloadPakFile_FromCDN();

	UFUNCTION(BlueprintCallable)
	void CPP_MountAllPakFile();

private:
	void OnCompleteDownload(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void MountProcess(); 
};
