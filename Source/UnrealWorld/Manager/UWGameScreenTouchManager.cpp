// Fill out your copyright notice in the Description page of Project Settings.


#include "UWGameScreenTouchManager.h"

#include "Runtime/Engine/Classes/Camera/CameraActor.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void UUWGameScreenTouchManager::Init()
{
}

void UUWGameScreenTouchManager::Tick(float InDeltaTime)
{
	for (FTouchInfo& Info : TouchInfos)
	{
		if (Info.IsUpdated)
		{
			Info.IsUpdated = false;
		}

		Info.OldLocation = Info.CurLocation;
	}
}

void UUWGameScreenTouchManager::Release()
{
}

FTouchInfo* UUWGameScreenTouchManager::FindTouchInfo(ETouchIndex::Type InIndex)
{
	FTouchInfo* TargetInfo = TouchInfos.FindByPredicate([&InIndex](const FTouchInfo& InData)
	{
		return InData.Index == InIndex;
	});

	return TargetInfo;
}

void UUWGameScreenTouchManager::EmptyTouchInfos()
{
	TouchInfos.Empty();
}

void UUWGameScreenTouchManager::OnTouchPressed(ETouchIndex::Type InIndex, FVector InLocation)
{
	FTouchInfo TouchInfo;

	TouchInfo.Index = InIndex;
	TouchInfo.CurLocation = InLocation;
	TouchInfo.StartLocation = InLocation;
	TouchInfo.OldLocation = InLocation;
	TouchInfo.IsUpdated = true;

	AddTouchInfo(TouchInfo);
}

void UUWGameScreenTouchManager::OnTouchRepeated(ETouchIndex::Type InIndex, FVector InLocation)
{
	if (FTouchInfo* TargetInfo = FindTouchInfo(InIndex))
	{
		if (TargetInfo->IsUpdated == false)
		{
			TargetInfo->OldLocation = TargetInfo->CurLocation;
		}

		TargetInfo->CurLocation = InLocation;
		TargetInfo->IsUpdated = true;
	}
}

void UUWGameScreenTouchManager::OnTouchReleased(ETouchIndex::Type InIndex, FVector InLocation)
{
	EmptyTouchInfos();
}
