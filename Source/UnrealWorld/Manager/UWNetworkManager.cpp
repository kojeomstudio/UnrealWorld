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

	// mapping
	RequestToCallbackMap.Add(Request, InCallback);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetStringField("model", Model);
	JsonObject->SetStringField("prompt", InQuery);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	Request->SetContentAsString(RequestBody);

	//Request->OnProcessRequestComplete().BindUObject(this, &UUWNetworkManager::OnResponse_Generate);

	Request->OnProcessRequestComplete().BindLambda(
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
	);

	Request->ProcessRequest();
}

void UUWNetworkManager::OnResponse_Generate(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Ollama Response >>> %s"), *Response->GetContentAsString());

		if (FOllamaAPIResDelegate* Find = RequestToCallbackMap.Find(Request))
		{
			Find->ExecuteIfBound(Response->GetContentAsString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OnResponse_Generate() >>> Error"));
	}

	RequestToCallbackMap.Remove(Request);
}
