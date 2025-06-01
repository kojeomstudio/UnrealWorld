// Fill out your copyright notice in the Description page of Project Settings.


#include "UWActorState.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/AIModule/Classes/BrainComponent.h"

#include "UnrealWorld/Character/UWActorBase.h"
#include "UnrealWorld/AI/UWAIController.h"

void FAttackState::Start()
{
	if (OwnerActor != nullptr)
	{
		OwnerActor->PlayAnimation(EActorAnimType::Attack);
	}
}

void FAttackState::Tick(float DeltaTime)
{
}

void FAttackState::End()
{
}

void FPatrolState::Start()
{
	if (OwnerActor != nullptr)
	{
		OwnerActor->PlayAnimation(EActorAnimType::Walk);
	}
}

void FPatrolState::Tick(float DeltaTime)
{
}

void FPatrolState::End()
{
}

void FMoveToState::Start()
{
	if (OwnerActor != nullptr)
	{
		OwnerActor->PlayAnimation(EActorAnimType::Run);
	}
}

void FMoveToState::Tick(float DeltaTime)
{
}

void FMoveToState::End()
{
}

void FSpeakToState::Start()
{
	if (OwnerActor != nullptr)
	{
		OwnerActor->PlayAnimation(EActorAnimType::Idle);
	}
}

void FSpeakToState::Tick(float DeltaTime)
{
}

void FSpeakToState::End()
{
}

void FIdleState::Start()
{
	if (OwnerActor != nullptr)
	{
		OwnerActor->PlayAnimation(EActorAnimType::Idle);
	}
}

void FIdleState::Tick(float DeltaTime)
{
}

void FIdleState::End()
{
}
