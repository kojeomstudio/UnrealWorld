// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnrealWorldInGameMode.h"
//#include "Runtime/Online/HTTP/Public/HttpManager.h"
//#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"
//#include "Runtime/PakFile/Public/IPlatformFilePak.h"

#include "UnrealWorld/Common/UWEssentialHeaders.h"
#include "UnrealWorld/Manager/UWGameCameraManager.h"
#include "UnrealWorld/Manager/UWGameWorldContextManager.h"
#include "UnrealWorld/Manager/UWGameActorManager.h"
#include "UnrealWorld/Config/UWGameConfigManager.h"

#include "UnrealWorld/Data/UWGameBPAsset.h"

#include "Runtime/Engine/Classes/GameFramework/PlayerStart.h"

void AUnrealWorldInGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UE_LOG(LogTemp, Log, TEXT("AUnrealWorldInGameMode::InitGame() >>> [MapName : %s]"), *MapName);

}

void AUnrealWorldInGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AUnrealWorldInGameMode::StartPlay()
{
	Super::StartPlay();

	UE_LOG(LogTemp, Log, TEXT("AUnrealWorldInGameMode::StartPlay()"));

	// Player Camaera
	{
		FGameCameraInitParams Params
		(
			FTransform::Identity,
			UW::GetDataAsset<UUWGameBPAsset>().PlayerGameCameraActorBP
		);

		UW::Get<UUWGameCameraManager>().SpawnCamera(Params);
	}
	

#if WITH_EDITOR
	UUWGameActorManager& GameActorManager = UW::Get<UUWGameActorManager>();
	GameActorManager.Spawn_Test();
#endif

	// Game World Context Update Init.
	if (UWorld* TargetWorld = GetWorld())
	{
		const float IntervalTimeSec = FGameConfigManager::GetFloatValue(FString(TEXT("AI")), FString(TEXT("RequestGenIntervalTimeSec")));

		TargetWorld->GetTimerManager().SetTimer(
			WorldContextUpdateHandle,
			this,
			&AUnrealWorldInGameMode::UpdateContext,
			IntervalTimeSec,
			true, 0.0f
		);
	}
}

void AUnrealWorldInGameMode::UpdateContext()
{
	UE_LOG(LogTemp, Log, TEXT("AUnrealWorldInGameMode::UpdateContext()"));

	UUWGameWorldContextManager& WorldContextManager = UW::Get<UUWGameWorldContextManager>();
	WorldContextManager.Update();
}
