// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnrealWorld/Manager/UWManagerBase.h"
#include "UWGameScreenTouchManager.generated.h"

/**
 * 
 */

struct FTouchInfo
{
public:
	ETouchIndex::Type Index = ETouchIndex::Type::MAX_TOUCHES;
	FVector StartLocation = FVector::ZeroVector;
	FVector CurLocation = FVector::ZeroVector;
	FVector OldLocation = FVector::ZeroVector;
	bool IsUpdated = false;
};

UCLASS()
class UNREALWORLD_API UUWGameScreenTouchManager : public UUWManagerBase
{
	GENERATED_BODY()
	
public:
	// Inherited via UUWManagerBase
	virtual void Init() override;
	virtual void Tick(float InDeltaTime) override;
	virtual void Release() override;

	// getters.
public:
	const TArray<FTouchInfo>& GetTouchInfos() { return TouchInfos; }

	FTouchInfo* FindTouchInfo(ETouchIndex::Type InIndex);

	// setters.
public:
	void AddTouchInfo(const FTouchInfo& InNewInfo)
	{
		TouchInfos.Add(InNewInfo);
	}

public:
	void EmptyTouchInfos();

	/// <summary>
	/// Call from PlayerGameCharacter (Pawn)
	/// </summary>
	/// <param name="InIndex"></param>
	/// <param name="InLocation"></param>
	void OnTouchPressed(ETouchIndex::Type InIndex, FVector InLocation);
	void OnTouchRepeated(ETouchIndex::Type InIndex, FVector InLocation);
	void OnTouchReleased(ETouchIndex::Type InIndex, FVector InLocation);

private:
	TArray<FTouchInfo> TouchInfos;
};
