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
#include "UnrealWorld/AI/UWAIController.h"

#include "UnrealWorld/Common/UWUtils.h"

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

	TArray<FPromptActorInfo> ActorInfos;

	UUWGameActorManager& GameActorManager = UW::Get<UUWGameActorManager>();
	for (const TPair<FGuid, TObjectPtr<AUWActorBase>>& Pair : GameActorManager.GetSpawnedActors())
	{
		const FGuid& Id = Pair.Key;
		if (const TObjectPtr<AUWActorBase> Actor = Pair.Value)
		{
			const FString& StateTypeString = UWUtils::EnumToString(Actor->GetStateType());
			const FString& ClassTypeString = UWUtils::EnumToString(Actor->GetClassType());

			ActorInfos.Add(FPromptActorInfo(Id.ToString(), StateTypeString, ClassTypeString));
		}
	}

	const FString& SystemPrompt = FGameWorldContextPrompt::GetSystemPrompt();
	const FString& ContextPrompt = FGameWorldContextPrompt::BuildUserPrompt(ActorInfos);
	const FString ResultPrompt = FString::Printf(TEXT("%s %s"), *SystemPrompt, *ContextPrompt);
	
	NetworkManager.Request_Generate(ResultPrompt, Callback);
}

void UUWGameWorldContextManager::OnUpdate_Internal(const FString& InResult)
{
	//UE_LOG(LogTemp, Log, TEXT("UUWGameWorldContextManager >>> OnUpdate_Internal() : %s"), *InResult);

	TArray<FLLMCommand> OutParsedCommands;
	if (CommandParser->Parse(InResult, OutParsedCommands))
	{
		OnUpdateWorldContext.Broadcast(OutParsedCommands);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to parse commands from LLM response."));
	}
}
