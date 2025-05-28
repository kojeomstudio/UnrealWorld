// Fill out your copyright notice in the Description page of Project Settings.


#include "UWGameWorldContextManager.h"

#include "Runtime/Engine/Classes/Camera/CameraActor.h"
#include "Runtime/Engine/Classes/Engine/World.h"

#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

// LLM
#include "UnrealWorld/LLM/LLMCommandParser.h"
#include "UnrealWorld/LLM/LLMPrompt.h"
// ~LLM

#include "UnrealWorld/UWPlatformGameInstance.h"
#include "UnrealWorld/Manager/UWNetworkManager.h"

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
}

void UUWGameWorldContextManager::Parse(const FString& InContent)
{
	// In response handler
	FLLMCommand ParsedCommand;
	if (CommandParser->Parse(InContent, ParsedCommand))
	{
	}
}

void UUWGameWorldContextManager::DispatchToAI(const FLLMCommand& Command, AAIController* Controller)
{
	UBlackboardComponent* BB = Controller->GetBlackboardComponent();
	if (BB == nullptr)
	{
		return;
	}

	switch (Command.GetCommandType())
	{
	case ELLMCommandType::MoveTo:
		BB->SetValueAsName(TEXT("TargetName"), FName(*Command.GetTarget()));
		break;
	case ELLMCommandType::Attack:
		BB->SetValueAsBool(TEXT("ShouldAttack"), true);
		break;
	case ELLMCommandType::PlayAnimation:
		BB->SetValueAsName(TEXT("AnimationName"), FName(*Command.GetTarget()));
		break;
	case ELLMCommandType::Speak:
		// Custom dialogue logic
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Unknown command type"));
		break;
	}
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
	Callback.BindUObject(this, &UUWGameWorldContextManager::Update_Internal);

	NetworkManager.Request_Generate(FString(), Callback);
}

void UUWGameWorldContextManager::Update_Internal(const FString& InResult)
{
	UE_LOG(LogTemp, Log, TEXT("UUWGameWorldContextManager >>> Update_Internal() : %s"), *InResult);
}
