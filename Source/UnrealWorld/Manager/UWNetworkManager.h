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

struct FOllamaResponseParsed
{
    // �� �̸� (��: "gemma3:1b")
    FString Model;
    // ���� ���� �ð� (ISO 8601 ������ Ÿ�ӽ�����)
    FString CreatedAt;
    // ���� ����� ���� �ؽ�Ʈ (```json ... ``` ��ũ�ٿ� ���Ե� �� ���� �� �Ľ� �ʿ�)
    FString Response;
    // ���� �Ϸ� ���� (true�� ���� ����, false�� ��Ʈ���� ��)
    bool bDone = false;
    // ���� ���� ���� ("stop", "length", "max_tokens" ��)
    FString DoneReason;
    // �� �Է� ������Ʈ�� ��ū ID ���
    TArray<int32> Context;
    // ��ü ���� �ҿ� �ð� (������ ����)
    int64 TotalDuration = 0;
    // �� �ε� �ҿ� �ð� (������ ����)
    int64 LoadDuration = 0;
    // ������Ʈ �� �� ���� ��ū ��
    int32 PromptEvalCount = 0;
    // ������Ʈ �� �ҿ� �ð� (������ ����)
    int64 PromptEvalDuration = 0;
    // ������ ��� ��ū ��
    int32 EvalCount = 0;
    // ��� ������ �ҿ�� �ð� (������ ����)
    int64 EvalDuration = 0;
    // �߷� ����
    FString Think;
};


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
	void Request_Generate(const FString& InQuery, FOllamaAPIResDelegate InCallback);

private:
	void OnResponse_Generate(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

private:
	TMap<FHttpRequestPtr, FOllamaAPIResDelegate> RequestToCallbackMap;
};
