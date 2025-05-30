// Fill out your copyright notice in the Description page of Project Settings.


#include "UWGameActorManager.h"

#include "Runtime/Engine/Classes/Engine/World.h"

#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

#include "UnrealWorld/UWPlatformGameInstance.h"
#include "UnrealWorld/Data/UWGameBPAsset.h"
#include "UnrealWorld/Character/UWActorBase.h"

void UUWGameActorManager::Init()
{
}

void UUWGameActorManager::Tick(float InDeltaTime)
{
}

void UUWGameActorManager::Release()
{
	SpawnedActors.Empty();
}

void UUWGameActorManager::Spawn(const FTId& InTId)
{
	// make by template data.
}

#if WITH_EDITOR
void UUWGameActorManager::Spawn_Test()
{
	UUWGameBPAsset& BPAsset = UW::GetDataAsset<UUWGameBPAsset>();

	FSpawnParams_Internal Test_SpawnParam0;

	Test_SpawnParam0.Class = BPAsset.GameNPCAsset.Get();
	Test_SpawnParam0.Location = FVector::ZeroVector;
	Test_SpawnParam0.Rotation = FRotator::ZeroRotator;

	Spawn_Internal(Test_SpawnParam0);
}
#endif

void UUWGameActorManager::Spawn_Internal(const FSpawnParams_Internal& InParams)
{
	if (UWorld* World = GetWorld())
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AActor* Actor = World->SpawnActor<AActor>(
			InParams.Class,
			InParams.Location,
			InParams.Rotation,
			ActorSpawnParams
		);

		if (AUWActorBase* ActorBase = Cast<AUWActorBase>(Actor))
		{
			const FGuid& Guid = FGuid::NewGuid();

			ActorBase->SetGuId(Guid);
			SpawnedActors.Add(Guid, ActorBase);
		}
	}
}
