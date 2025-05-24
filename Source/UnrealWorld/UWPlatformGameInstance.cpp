// Fill out your copyright notice in the Description page of Project Settings.


#include "UWPlatformGameInstance.h"

#include "Data/UWGameBPAsset.h"

#include "UnrealWorld/Manager/UWManagerBase.h"
#include "UnrealWorld/Manager/UWGameCameraManager.h"
#include "UnrealWorld/Manager/UWGameDataManager.h"
#include "UnrealWorld/Manager/UWGameScreenTouchManager.h"

#include "Runtime/Core/Public/Containers/Ticker.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/AssetRegistry/Public/AssetRegistry/AssetRegistryModule.h"
#include "Runtime/Engine/Classes/Engine/ObjectLibrary.h"

#include "UnrealWorld/Character/PlayerGameCharacter.h"
#include "UnrealWorld/UWPlayerController.h"

#include "UnrealWorld/Config/UWGameIniConfig.h"



UUWPlatformGameInstance* UUWPlatformGameInstance::Instance = nullptr;

void UUWPlatformGameInstance::Init()
{
	Super::Init();

	Instance = this;

	GameIniConfig = NewObject<UUWGameIniConfig>();

	InitManagers();
	InitDataAssets();

	TickDelegateHandle.Reset();
	TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UUWPlatformGameInstance::TickProcess));
}

void UUWPlatformGameInstance::Shutdown()
{
	// release everything.
	TickDelegateHandle.Reset();
	DataAssets.Empty();
	Managers.Empty();
	GameIniConfig = nullptr;
}

APlayerGameCharacter* UUWPlatformGameInstance::GetMyPawn()
{
	if (AUWPlayerController* MyPlayerController = GetMyController())
	{
		return Cast<APlayerGameCharacter>(MyPlayerController->GetPawn()); // get possesed pawn. ( my )
	}

	return nullptr;
}

AUWPlayerController* UUWPlatformGameInstance::GetMyController()
{
	if (UWorld* CurWorld = GetWorld())
	{
		if (APlayerController* PlayerController = CurWorld->GetFirstPlayerController())
		{
			return Cast<AUWPlayerController>(PlayerController);
		}
	}

	return nullptr;
}

void UUWPlatformGameInstance::InitManagers()
{
	Managers.Empty();

	for (UClass* Class : TObjectRange<UClass>())
	{
		if (Class)
		{
			if (Class->IsChildOf(UUWManagerBase::StaticClass()) &&
				(Class->HasAnyClassFlags(EClassFlags::CLASS_Abstract) == false))
			{
				if (UUWManagerBase* NewInst = Managers.Add(Class, NewObject<UUWManagerBase>(this, Class)))
				{
					NewInst->Init();
				}
			}
		}
	}
}

UUWGameIniConfig* UUWPlatformGameInstance::GetGameIniConfig()
{
	return GameIniConfig.Get();
}

void UUWPlatformGameInstance::InitDataAssets()
{
	DataAssets.Empty();

	const FString FolderPath = TEXT("/Game/DataAsset/");

	UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(UObject::StaticClass(), true, false);

	ObjectLibrary->AddToRoot();
	ObjectLibrary->LoadAssetDataFromPath(FolderPath);

	TArray<FAssetData> AssetDataList;
	ObjectLibrary->GetAssetDataList(AssetDataList);

	for (const FAssetData& AssetData : AssetDataList)
	{
		UObject* LoadedObject = AssetData.GetAsset();

		if (LoadedObject)
		{
			DataAssets.Add(LoadedObject->GetClass(), Cast<UDataAsset>(LoadedObject));
		}
	}

	ObjectLibrary->ClearLoaded();
	ObjectLibrary->RemoveFromRoot();
	ObjectLibrary->ConditionalBeginDestroy();
}

bool UUWPlatformGameInstance::TickProcess(float InDeltaTime)
{
	for (TPair<UClass*, UUWManagerBase*>& Item : Managers)
	{
		if (UUWManagerBase* ManagerInst = Item.Value)
		{
			ManagerInst->Tick(InDeltaTime);
		}
	}

	return true;
}
