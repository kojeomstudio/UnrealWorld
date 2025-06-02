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
    // 모델 이름 (예: "gemma3:1b")
    FString Model;
    // 응답 생성 시각 (ISO 8601 형식의 타임스탬프)
    FString CreatedAt;
    // 모델이 출력한 응답 텍스트 (```json ... ``` 마크다운 포함됨 → 제거 후 파싱 필요)
    FString Response;
    // 생성 완료 여부 (true면 생성 종료, false면 스트리밍 중)
    bool bDone = false;
    // 생성 종료 이유 ("stop", "length", "max_tokens" 등)
    FString DoneReason;
    // 모델 입력 프롬프트의 토큰 ID 목록
    TArray<int32> Context;
    // 전체 응답 소요 시간 (나노초 단위)
    int64 TotalDuration = 0;
    // 모델 로딩 소요 시간 (나노초 단위)
    int64 LoadDuration = 0;
    // 프롬프트 평가 시 사용된 토큰 수
    int32 PromptEvalCount = 0;
    // 프롬프트 평가 소요 시간 (나노초 단위)
    int64 PromptEvalDuration = 0;
    // 생성된 출력 토큰 수
    int32 EvalCount = 0;
    // 출력 생성에 소요된 시간 (나노초 단위)
    int64 EvalDuration = 0;
    // 추론 영역
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
