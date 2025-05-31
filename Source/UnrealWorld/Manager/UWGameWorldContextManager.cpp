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
	FLLMCommand ParsedCommand;
	if (CommandParser->Parse(InResult, ParsedCommand))
	{
	}
}
