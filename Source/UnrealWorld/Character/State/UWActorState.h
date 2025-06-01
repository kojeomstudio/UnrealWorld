// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealWorld/Common/UWEnums.h"

class USkeletalMeshComponent;
class AUWActorBase;

struct FActorStateBase
{
public:
	virtual ~FActorStateBase() {}

	FActorStateBase(EActorStateType InStateType, AUWActorBase* InOwnerActor)
		: StateType(InStateType), OwnerActor(InOwnerActor) {}

	virtual void Start() = 0;
	virtual void Tick(float DeltaTime) = 0;
	virtual void End() = 0;

protected:
	EActorStateType StateType = EActorStateType::Unknown;
	TObjectPtr<AUWActorBase> OwnerActor = nullptr;
};

struct FAttackState : public FActorStateBase
{
public:
	FAttackState(AUWActorBase* InOwnerActor)
		: FActorStateBase(EActorStateType::Attack, InOwnerActor) {}
	virtual void Start() override;
	virtual void Tick(float DeltaTime) override;
	virtual void End() override;
};

struct FPatrolState : public FActorStateBase
{
public:
	FPatrolState(AUWActorBase* InOwnerActor)
		: FActorStateBase(EActorStateType::Patrol, InOwnerActor) {}
	virtual void Start() override;
	virtual void Tick(float DeltaTime) override;
	virtual void End() override;
};

struct FMoveToState : public FActorStateBase
{
public:
	FMoveToState(AUWActorBase* InOwnerActor)
		: FActorStateBase(EActorStateType::MoveTo, InOwnerActor) {}
	virtual void Start() override;
	virtual void Tick(float DeltaTime) override;
	virtual void End() override;
};

struct FSpeakToState : public FActorStateBase
{
public:
	FSpeakToState(AUWActorBase* InOwnerActor)
		: FActorStateBase(EActorStateType::SpeakTo, InOwnerActor) {}
	virtual void Start() override;
	virtual void Tick(float DeltaTime) override;
	virtual void End() override;
};

struct FIdleState : public FActorStateBase
{
public:
	FIdleState(AUWActorBase* InOwnerActor)
		: FActorStateBase(EActorStateType::Idle, InOwnerActor) {}
	virtual void Start() override;
	virtual void Tick(float DeltaTime) override;
	virtual void End() override;
};