// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnrealWorldGameModeBase.h"

void AUnrealWorldGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UE_LOG(LogTemp, Log, TEXT("AUnrealWorldGameModeBase::InitGame [MapName : %s]"), *MapName);
}
