// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnrealWorld/Manager/UWManagerBase.h"
#include "UnrealWorld/Common/UWEnums.h"
#include "UnrealWorld/Data/UWData.h"

// LLM
#include "UnrealWorld/LLM/LLMCommand.h"
// ~LLM

#include "UWGameActorManager.generated.h"

class AAIController;
class AUWActorBase;

/**
 * 
 */


UCLASS()
class UNREALWORLD_API UUWGameActorManager : public UUWManagerBase
{
	GENERATED_BODY()

private:
	struct FSpawnParams_Internal
	{
	public:
		FSpawnParams_Internal() = default;
	public:
		TSubclassOf<AActor> Class;
		FVector Location;
		FRotator Rotation;
		EActorClassType ActorClassType = EActorClassType::Novice; // Default to Novice

		TObjectPtr<UAnimSequenceBase> IdleAnim;
		TObjectPtr<UAnimSequenceBase> WalkAnim;
		TObjectPtr<UAnimSequenceBase> RunAnim;
		TObjectPtr<UAnimSequenceBase> AttackAnim;
	};
	
public:
	// Inherited via UUWManagerBase
	virtual void Init() override;
	virtual void PostInit() override;
	virtual void Tick(float InDeltaTime) override;
	virtual void Release() override;

public:
	void Spawn(const FTId& InTId);

#if WITH_EDITOR
	void Spawn_Test();
#endif

public:
	const TMap<FGuid, AUWActorBase*>& GetSpawnedActors()
	{
		return SpawnedActors;
	}

private:
	void Spawn_Internal(const FSpawnParams_Internal& InParams);
	void OnUpdateWorldContext(const TArray<FLLMCommand>& InCommands);

private:
	UPROPERTY(Transient)
	TMap<FGuid, AUWActorBase*> SpawnedActors;

	FDelegateHandle OnUpdateWorldContextHandle;
};
