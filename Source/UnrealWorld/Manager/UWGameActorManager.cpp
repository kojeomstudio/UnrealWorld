// Fill out your copyright notice in the Description page of Project Settings.


#include "UWGameActorManager.h"

#include "Runtime/Engine/Classes/Engine/World.h"

#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

#include "UnrealWorld/UWPlatformGameInstance.h"
#include "UnrealWorld/Data/UWGameBPAsset.h"

#include "UnrealWorld/Character/UWActorBase.h"
#include "UnrealWorld/Character/UWGameNpc.h"
#include "UnrealWorld/Character/UWGameMonster.h"
#include "UnrealWorld/Character/UWPlayerSpectator.h"
#include "UnrealWorld/Character/UWPlayerCharacter.h"
#include "UnrealWorld/AI/AICommands.h"
#include "UnrealWorld/AI/UWAIController.h"

#include "UnrealWorld/Manager/UWGameWorldContextManager.h"

void UUWGameActorManager::Init()
{
}

void UUWGameActorManager::PostInit()
{
	UUWGameWorldContextManager& WorldContextManager = UW::Get<UUWGameWorldContextManager>();
	OnUpdateWorldContextHandle = WorldContextManager.OnUpdateWorldContext.AddUObject(this, &UUWGameActorManager::OnUpdateWorldContext);
}

void UUWGameActorManager::Tick(float InDeltaTime)
{
}

void UUWGameActorManager::Release()
{
	SpawnedActors.Empty();

	UUWGameWorldContextManager& WorldContextManager = UW::Get<UUWGameWorldContextManager>();
	WorldContextManager.OnUpdateWorldContext.Remove(OnUpdateWorldContextHandle);
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

	Test_SpawnParam0.Class = BPAsset.GameNPCAsset.LoadSynchronous();
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

void UUWGameActorManager::OnUpdateWorldContext(const TArray<FLLMCommand>& InCommands)
{
	for (const FLLMCommand& Command : InCommands)
	{
		if (AUWActorBase* FindActor = *(SpawnedActors.Find(FGuid(Command.GetUniqueId()))))
		{
			if (AUWAIController* AIController = Cast<AUWAIController>(FindActor->GetController()))
			{
				FBaseAICommand* AICommand = nullptr;
				// Apply command to the actor
				switch (Command.GetCommandType())
				{
				case EActorStateType::Attack:
					AICommand = new FAttackCommand(Command.GetTarget());
					break;
				case EActorStateType::Patrol:
					AICommand = new FPatrolCommand(Command.GetTarget());
					break;
				case EActorStateType::MoveTo:
					AICommand = new FMoveToCommand(Command.GetTarget());
					break;
				case EActorStateType::SpeakTo:
					AICommand = new FSpeakToCommand(Command.GetTarget());
					break;
				case EActorStateType::Idle:
					AICommand = new FIdleCommand(Command.GetTarget());
					break;
				}

				if (AICommand != nullptr)
				{
					AICommand->Execute(AIController);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Actor %s does not have a valid AIController."), *FindActor->GetName());
			}
		}
	}
}
