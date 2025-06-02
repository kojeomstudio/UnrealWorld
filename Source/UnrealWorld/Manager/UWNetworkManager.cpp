// Fill out your copyright notice in the Description page of Project Settings.


#include "UWNetworkManager.h"

#include "Runtime/Engine/Classes/Camera/CameraActor.h"
#include "Runtime/Engine/Classes/Engine/World.h"

#include "UnrealWorld/UWPlatformGameInstance.h"
#include "UnrealWorld/Config/UWGameConfigManager.h"

constexpr int32 SUCCESS_CODE = 200;

void UUWNetworkManager::Init()
{
}

void UUWNetworkManager::Tick(float InDeltaTime)
{
}

void UUWNetworkManager::Release()
{
	RequestToCallbackMap.Empty();
}


void UUWNetworkManager::Request_Generate(const FString& InQuery, FOllamaAPIResDelegate InCallback)
{
	// ollama api
	// https://github.com/ollama/ollama/blob/main/docs/api.md

	FString APIUrl;
#if !UE_BUILD_SHIPPING
	APIUrl = FGameConfigManager::GetStringValue(FString(TEXT("OllamaAPI")), FString(TEXT("Dev")));
#else
	APIUrl = FGameConfigManager::GetStringValue(FString(TEXT("OllamaAPI")), FString(TEXT("Live")));
#endif
	FString TargetURL = FString::Printf(TEXT("%s/api/generate"), *APIUrl);

	const FString& Model = FGameConfigManager::GetStringValue(FString(TEXT("OllamaAPI")), FString(TEXT("Model")));

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TargetURL);
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	const float TimeOutSec = FGameConfigManager::GetFloatValue(FString(TEXT("OllamaAPI")), FString(TEXT("TimeOutSec")));
	Request->SetTimeout(TimeOutSec);

	// mapping
	RequestToCallbackMap.Add(Request, InCallback);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetStringField("model", Model);
	JsonObject->SetStringField("prompt", InQuery);
	JsonObject->SetBoolField("stream", false);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	Request->SetContentAsString(RequestBody);

	Request->OnProcessRequestComplete().BindUObject(this, &UUWNetworkManager::OnResponse_Generate);
	/*Request->OnProcessRequestComplete().BindLambda(
		[InCallback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			if (bWasSuccessful && Response.IsValid())
			{
				const FString& Result = Response->GetContentAsString();
				InCallback.ExecuteIfBound(Result);
			}
			else
			{
				InCallback.ExecuteIfBound(TEXT("ERROR"));
			}
		}
	);*/

	Request->ProcessRequest();
}

void UUWNetworkManager::OnResponse_Generate(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("OnResponse_Generate() >>> HTTP request failed or invalid response."));
		RequestToCallbackMap.Remove(Request);
		return;
	}

	const FString RawContent = Response->GetContentAsString();
	UE_LOG(LogTemp, Log, TEXT("Ollama Raw Response >>> %s"), *RawContent);

	// 1차 JSON 파싱
	TSharedPtr<FJsonObject> RootObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(RawContent);

	if (!FJsonSerializer::Deserialize(Reader, RootObject) || !RootObject.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON root from Ollama response."));
		RequestToCallbackMap.Remove(Request);
		return;
	}

	FOllamaResponseParsed Parsed;
	RootObject->TryGetStringField(TEXT("model"), Parsed.Model);
	RootObject->TryGetStringField(TEXT("created_at"), Parsed.CreatedAt);
	RootObject->TryGetBoolField(TEXT("done"), Parsed.bDone);
	RootObject->TryGetStringField(TEXT("done_reason"), Parsed.DoneReason);
	RootObject->TryGetNumberField(TEXT("total_duration"), Parsed.TotalDuration);
	RootObject->TryGetNumberField(TEXT("load_duration"), Parsed.LoadDuration);
	RootObject->TryGetNumberField(TEXT("prompt_eval_count"), Parsed.PromptEvalCount);
	RootObject->TryGetNumberField(TEXT("prompt_eval_duration"), Parsed.PromptEvalDuration);
	RootObject->TryGetNumberField(TEXT("eval_count"), Parsed.EvalCount);
	RootObject->TryGetNumberField(TEXT("eval_duration"), Parsed.EvalDuration);

#if WITH_EDITOR
	UE_LOG(LogTemp, Log, TEXT("@@@ Ollama Response Info @@@"));

	double DurationSec = Parsed.TotalDuration / 1000000000.0;
	const FString DurationStr = FString::Printf(TEXT("%.2f"), DurationSec);  // 소수점 6자리까지 출력

	UE_LOG(LogTemp, Log, TEXT("Model : %s \n Total Duration : %s(sec) \n "), 
		*Parsed.Model, *DurationStr);
#endif

	const TArray<TSharedPtr<FJsonValue>>* ContextArray;
	if (RootObject->TryGetArrayField(TEXT("context"), ContextArray))
	{
		for (const TSharedPtr<FJsonValue>& Value : *ContextArray)
		{
			int32 Token;
			if (Value->TryGetNumber(Token))
			{
				Parsed.Context.Add(Token);
			}
		}
	}

	// "response" 필드: JSON 문자열이 마크다운으로 감싸져 있음
	if (!RootObject->TryGetStringField(TEXT("response"), Parsed.Response))
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing 'response' field in Ollama JSON."));
		RequestToCallbackMap.Remove(Request);
		return;
	}

	// <think> 태그 처리
	FString ModelThink;
	const FString ThinkStart = TEXT("<think>");
	const FString ThinkEnd = TEXT("</think>");
	int32 StartIndex, EndIndex;

	if (Parsed.Response.FindChar('<', StartIndex) && Parsed.Response.Find(ThinkStart, ESearchCase::IgnoreCase, ESearchDir::FromStart, StartIndex) != INDEX_NONE)
	{
		StartIndex = Parsed.Response.Find(ThinkStart);
		EndIndex = Parsed.Response.Find(ThinkEnd, ESearchCase::IgnoreCase, ESearchDir::FromStart, StartIndex);

		if (StartIndex != INDEX_NONE && EndIndex != INDEX_NONE && EndIndex > StartIndex)
		{
			int32 ContentStart = StartIndex + ThinkStart.Len();
			int32 ContentLen = EndIndex - ContentStart;

			// 추출
			ModelThink = Parsed.Response.Mid(ContentStart, ContentLen);

			// 제거
			Parsed.Response.RemoveAt(StartIndex, (EndIndex + ThinkEnd.Len()) - StartIndex);
		}
	}
	Parsed.Think = ModelThink;

	// 마크다운 제거
	Parsed.Response.ReplaceInline(TEXT("```json\n"), TEXT(""));
	Parsed.Response.ReplaceInline(TEXT("```"), TEXT(""));
	Parsed.Response.TrimStartAndEndInline();

	if (Parsed.Think.IsEmpty() == false)
	{
		UE_LOG(LogTemp, Log, TEXT("Ollama Modle-Think >>> %s"), *Parsed.Think);
	}
	UE_LOG(LogTemp, Log, TEXT("Ollama Response >>> %s"), *Parsed.Response);

	// 파싱된 JSON 응답을 delegate로 전달
	if (FOllamaAPIResDelegate* Find = RequestToCallbackMap.Find(Request))
	{
		Find->ExecuteIfBound(Parsed.Response);
	}

	RequestToCallbackMap.Remove(Request);
}


