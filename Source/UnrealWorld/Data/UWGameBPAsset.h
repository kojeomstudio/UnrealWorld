// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealWorld/Data/UWGameDataAssetBase.h"
#include "UnrealWorld/Common/UWEnums.h"
#include "UWGameBPAsset.generated.h"

class AUWPlayerCharacter;
class ASpectatorCameraActor;
class APlayerGameCameraActor;
class AUWPlayerSpectator;
class AUWGameMonster;
class AUWGameNpc;
class AUWActorBase;
class UAnimSequence;

USTRUCT(BlueprintType)
struct FActorBPData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<AUWActorBase> DefaultAsset;
	UPROPERTY(EditDefaultsOnly)
	EActorClassType DefaultClass;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimSequenceBase> IdleAnim;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimSequenceBase> WalkAnim;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimSequenceBase> RunAnim;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimSequenceBase> AttackAnim;
};

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

	UPROPERTY(Category = Actor, EditDefaultsOnly)
	FActorBPData NpcAsset;

	UPROPERTY(Category = Actor, EditDefaultsOnly)
	FActorBPData NoviceNpcAsset;

	UPROPERTY(Category = Actor, EditDefaultsOnly)
	FActorBPData MonsterAsset;
};
