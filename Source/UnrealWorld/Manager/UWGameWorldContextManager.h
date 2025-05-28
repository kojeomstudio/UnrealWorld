// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnrealWorld/Manager/UWManagerBase.h"

#include "UnrealWorld/LLM/LLMCommand.h"

#include "UWGameWorldContextManager.generated.h"

class FLLMCommandParser;
class AAIController;

/**
 * 
 */


UCLASS()
class UNREALWORLD_API UUWGameWorldContextManager : public UUWManagerBase
{
	GENERATED_BODY()
	
public:
	// Inherited via UUWManagerBase
	virtual void Init() override;
	virtual void Tick(float InDeltaTime) override;
	virtual void Release() override;

public:
	void Parse(const FString& InContent);
	void DispatchToAI(const FLLMCommand& Command, AAIController* Controller);
	void Update();

private:
	UFUNCTION()
	void Update_Internal(const FString& InResult);

private:
	TUniquePtr<FLLMCommandParser> CommandParser;
};
