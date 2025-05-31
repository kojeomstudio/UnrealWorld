// Fill out your copyright notice in the Description page of Project Settings.


#include "UWGameWorldContextManager.h"

#include "Runtime/Engine/Classes/Camera/CameraActor.h"
#include "Runtime/Engine/Classes/Engine/World.h"

#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

// LLM
#include "UnrealWorld/LLM/LLMPrompt.h"
// ~LLM

#include "UnrealWorld/UWPlatformGameInstance.h"
#include "UnrealWorld/Manager/UWNetworkManager.h"
#include "UnrealWorld/Manager/UWGameActorManager.h"
#include "UnrealWorld/Character/UWActorBase.h"
#include "UnrealWorld/AI/AICommands.h"

void UUWGameWorldContextManager::Init()
{
	// In Init()
	CommandParser = MakeUnique<FLLMCommandParser>();
}

void UUWGameWorldContextManager::Tick(float InDeltaTime)
{
}

void UUWGameWorldContextManager::Release()
{
	CommandParser.Reset();
}

void UUWGameWorldContextManager::Update()
{
	// update world context to llm

	UE_LOG(LogTemp, Log, TEXT("UUWGameWorldContextManager::Update()"));

	UUWNetworkManager& NetworkManager = UW::Get<UUWNetworkManager>();

	/*FOllamaAPIResDelegate Callback;
	Callback.BindLambda([](FString& InResult) {
		UE_LOG(LogTemp, Log, TEXT("UUWNetworkManager >>> Generate Response : %s"), *InResult);
	});*/

	FOllamaAPIResDelegate Callback;
	Callback.BindUObject(this, &UUWGameWorldContextManager::OnUpdate_Internal);

	TArray<TPair<FString, FString>> ActorInfos;

	UUWGameActorManager& GameActorManager = UW::Get<UUWGameActorManager>();
	for (const TPair<FGuid, AUWActorBase*>& Pair : GameActorManager.GetSpawnedActors())
	{
		const FGuid& Id = Pair.Key;
		if (const AUWActorBase* Actor = Pair.Value)
		{
			ActorInfos.Add(TPair<FString, FString>(Id.ToString(), Actor->GetName()));
		}
	}

	const FString& SystemPrompt = FGameWorldContextPrompt::GetSystemPrompt();
	const FString& ContextPrompt = FGameWorldContextPrompt::BuildUserPrompt(ActorInfos);
	const FString ResultPrompt = FString::Printf(TEXT("%s %s"), *SystemPrompt, *ContextPrompt);
	
	NetworkManager.Request_Generate(ResultPrompt, Callback);
}

void UUWGameWorldContextManager::OnUpdate_Internal(const FString& InResult)
{
	UE_LOG(LogTemp, Log, TEXT("UUWGameWorldContextManager >>> OnUpdate_Internal() : %s"), *InResult);

	// 여러 Actor에 대한 명령들을 분리해서 적용해야함..
	TArray<FLLMCommand> OutParsedCommands;
	if (CommandParser->Parse(InResult, OutParsedCommands))
	{
		UUWGameActorManager& GameActorManager = UW::Get<UUWGameActorManager>();
		const TMap<FGuid, AUWActorBase*>& Actors = GameActorManager.GetSpawnedActors();

		for (const FLLMCommand& Command : OutParsedCommands)
		{
			if (AUWActorBase* FindActor = *(Actors.Find(FGuid(Command.GetUniqueId()))))
			{
				if (AAIController* Controller = Cast<AAIController>(FindActor->GetController()))
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
						AICommand->Execute(Controller);
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Actor %s does not have a valid AIController."), *FindActor->GetName());
				}
			}
			
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to parse commands from LLM response."));
	}
}
