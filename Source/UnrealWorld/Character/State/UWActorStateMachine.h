// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "UWActorState.h"
#include "UnrealWorld/Common/UWEnums.h"

class USkeletalMeshComponent;
class AUWActorBase;

class FUWActorStateMachine
{
public:
	FUWActorStateMachine() = default;
	FUWActorStateMachine(AUWActorBase* InOwnerActor)
		: OwnerActor(InOwnerActor) {
	}

	void ChangeState(const EActorStateType InStateType);
	void Tick(float DeltaTime);

public:
	// Getters
	EActorStateType GetCurrentStateType() const { return CurrentStateType; }
	const FActorStateBase* GetCurrentState() const { return CurrentState.Get(); }

protected:
	TObjectPtr<AUWActorBase> OwnerActor;
	TUniquePtr<FActorStateBase> CurrentState;
	EActorStateType CurrentStateType = EActorStateType::Unknown;
};