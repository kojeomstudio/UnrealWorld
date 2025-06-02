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

#include "UnrealWorld/Common/UWUtils.h"

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

	auto MakeSpawnParam_Internal = [&BPAsset](int32 InRandSeed, EActorClassType InClassType) -> FSpawnParams_Internal
	{
		FRandomStream RandomStream;
		RandomStream.Initialize(InRandSeed);

		FSpawnParams_Internal Test_SpawnParam0;

		FActorBPData TargetBPData;
		if (InClassType == EActorClassType::Fighter)
		{
			TargetBPData = BPAsset.NpcAsset;
		}
		else if (InClassType == EActorClassType::Novice)
		{
			TargetBPData = BPAsset.NoviceNpcAsset;
		}
		Test_SpawnParam0.Class = TargetBPData.DefaultAsset.LoadSynchronous();

		FVector SpawnLocation = FVector::ZeroVector;
		SpawnLocation.Z += 100.0f;
		SpawnLocation.X += RandomStream.FRandRange(-600.0f, 700.0f);
		SpawnLocation.Y += RandomStream.FRandRange(-600.0f, 700.0f);

		Test_SpawnParam0.Location = SpawnLocation;
		Test_SpawnParam0.Rotation = FRotator::ZeroRotator;
		Test_SpawnParam0.ActorClassType = TargetBPData.DefaultClass;
		Test_SpawnParam0.IdleAnim = TargetBPData.IdleAnim;
		Test_SpawnParam0.WalkAnim = TargetBPData.WalkAnim;
		Test_SpawnParam0.RunAnim = TargetBPData.RunAnim;
		Test_SpawnParam0.AttackAnim = TargetBPData.AttackAnim;

		return Test_SpawnParam0;
	};

	Spawn_Internal(MakeSpawnParam_Internal(1, EActorClassType::Fighter));
	Spawn_Internal(MakeSpawnParam_Internal(32167, EActorClassType::Fighter));
	Spawn_Internal(MakeSpawnParam_Internal(9980, EActorClassType::Fighter));
	Spawn_Internal(MakeSpawnParam_Internal(12345, EActorClassType::Fighter));
	Spawn_Internal(MakeSpawnParam_Internal(5000, EActorClassType::Novice));
	Spawn_Internal(MakeSpawnParam_Internal(8080, EActorClassType::Novice));
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
			ActorBase->SetClass(InParams.ActorClassType);
			ActorBase->SetAnimationData(FActorAnimationData
			(
				InParams.IdleAnim,
				InParams.WalkAnim,
				InParams.RunAnim,
				InParams.AttackAnim
			));
			ActorBase->ChangeState(EActorStateType::Idle);

			SpawnedActors.Add(Guid, ActorBase);
		}
	}
}

void UUWGameActorManager::OnUpdateWorldContext(const TArray<FLLMCommand>& InCommands)
{
#if WITH_EDITOR
	int32 KeyIndex = 0;
	for (const FLLMCommand& Command : InCommands)
	{
		UWUtils::DebugLogToScreen(
			FString::Printf(TEXT("[Log] LLM Command \n Type : %s \n UId : %s \n Target : %s \n Reason : %s"),
				*UWUtils::EnumToString(Command.GetCommandType()), *Command.GetUniqueId(),
				*Command.GetTarget(), *Command.GetReason()),
			++KeyIndex,
			5.0f,
			FColor::Green);
	}
#endif

	for (const FLLMCommand& Command : InCommands)
	{
		if (AUWActorBase* FindActor = *(SpawnedActors.Find(FGuid(Command.GetUniqueId()))))
		{
			if (AUWAIController* AIController = Cast<AUWAIController>(FindActor->GetController()))
			{
				TUniquePtr<FBaseAICommand> AICommand = nullptr;
				// Apply command to the actor
				EActorStateType CommandType = Command.GetCommandType();
				switch (CommandType)
				{
				case EActorStateType::Attack:
					AICommand = MakeUnique<FAttackCommand>(Command.GetTarget());
					break;
				case EActorStateType::Patrol:
					AICommand = MakeUnique<FPatrolCommand>(Command.GetTarget());
					break;
				case EActorStateType::MoveTo:
					AICommand = MakeUnique<FMoveToCommand>(Command.GetTarget());
					break;
				case EActorStateType::SpeakTo:
					AICommand = MakeUnique<FSpeakToCommand>(Command.GetTarget());
					break;
				case EActorStateType::Idle:
					AICommand = MakeUnique<FIdleCommand>(Command.GetTarget());
					break;
				}

				if (AICommand.IsValid())
				{
					AICommand->Execute(AIController);
					FindActor->ChangeState(CommandType);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Actor %s does not have a valid AIController."), *FindActor->GetName());
			}
		}
	}
}
