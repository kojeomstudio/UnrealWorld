// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealWorld/Data/UWGameDataAssetBase.h"
#include "UWGameBPAsset.generated.h"

class APlayerGameCharacter;
class ASpectatorCameraActor;
class APlayerGameCameraActor;
class AUWPlayerSpectator;

/**
 * 
 */
UCLASS()
class UNREALWORLD_API UUWGameBPAsset : public UUWGameDataAssetBase
{
	GENERATED_BODY()
	

public:
	UPROPERTY(Category = Player, EditDefaultsOnly)
	TSoftClassPtr<AUWPlayerSpectator> SpectatorAsset;
	UPROPERTY(Category = Player, EditDefaultsOnly)
	TSubclassOf<AUWPlayerSpectator> SpectatorClass;

	UPROPERTY(Category = Player, EditAnywhere)
	TSubclassOf<APlayerGameCameraActor> PlayerGameCameraActorBP;
};
