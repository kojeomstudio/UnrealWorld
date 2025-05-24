// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnrealWorld/Manager/UWManagerBase.h"
#include "Http.h"
//#include "Runtime/Core/Public/Delegates/DelegateCombinations.h"
#include "Delegates/Delegate.h"

#include "UWNetworkManager.generated.h"

/**
 * 
 */

// https://github.com/ollama/ollama/blob/main/docs/api.md

DECLARE_DELEGATE_OneParam(FOllamaAPIResDelegate, const FString&)

UCLASS()
class UNREALWORLD_API UUWNetworkManager : public UUWManagerBase
{
	GENERATED_BODY()
	
public:
	// Inherited via UUWManagerBase
	virtual void Init() override;
	virtual void Tick(float InDeltaTime) override;
	virtual void Release() override;

public:

	//UFUNCTION(BlueprintCallable, Category = "OllamaAPI")
	void Generate(const FString& InQuery, FOllamaAPIResDelegate InCallback);

private:
	void OnResponse_Generate(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

private:
	TMap<FHttpRequestPtr, FOllamaAPIResDelegate> RequestToCallbackMap;
};
