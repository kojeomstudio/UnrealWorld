// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintPlatformLibrary.h"
#include "UWPlatformGameInstance.generated.h"

class UUWGameBPAsset;
class UUWManagerBase;
class UClass;
class UDataAsset;
class APlayerGameCharacter; // main pawn.
class AUWPlayerController;
class UUWGameIniConfig;
/**
 * 
 */
UCLASS()
class UNREALWORLD_API UUWPlatformGameInstance : public UPlatformGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;

public:
	static UUWPlatformGameInstance* Instance;

	// getters.
public:
	
	template<typename T>
	T& GetManager()
	{
		UUWManagerBase* Manager = *(Managers.Find(T::StaticClass()));
		check(Manager);

		return *(static_cast<T*>(Manager));
	}

	template<typename T>
	T& GetDataAsset()
	{
		UDataAsset* Data = *(DataAssets.Find(T::StaticClass()));
		check(Data);

		return *(static_cast<T*>(Data));
	}

	APlayerGameCharacter* GetMyPawn();
	AUWPlayerController* GetMyController();

	UUWGameIniConfig* GetGameIniConfig();

private:
	void InitManagers();
	void InitDataAssets();

	bool TickProcess(float InDeltaTime);

private:
	UPROPERTY(Transient)
	TMap<UClass*, UDataAsset*> DataAssets;

	UPROPERTY(Transient)
	TMap<UClass* ,UUWManagerBase*> Managers;

	UPROPERTY(Transient)
	TObjectPtr<UUWGameIniConfig> GameIniConfig;

private:
	FTSTicker::FDelegateHandle TickDelegateHandle;
};

/// <summary>
/// GameInstance Helper.
/// </summary>
namespace UW
{
	template<typename T>
	T& Get()
	{
		return UUWPlatformGameInstance::Instance->GetManager<T>();
	}

	template<typename T>
	T& GetDataAsset()
	{
		return UUWPlatformGameInstance::Instance->GetDataAsset<T>();
	}

	FORCEINLINE UUWPlatformGameInstance* GetPlatformInstance()
	{
		return UUWPlatformGameInstance::Instance;
	}
}
