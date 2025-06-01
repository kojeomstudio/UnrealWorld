// Fill out your copyright notice in the Description page of Project Settings.


#include "UWActorStateMachine.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/AIModule/Classes/BrainComponent.h"

#include "UnrealWorld/AI/UWAIController.h"
#include "UnrealWorld/Common/UWUtils.h"

void FUWActorStateMachine::ChangeState(const EActorStateType InStateType)
{
	if (CurrentState.IsValid() && CurrentStateType == InStateType)
	{
		// Already in the requested state, no need to change.
		return;
	}

	if (CurrentState.IsValid())
	{
		// End the current state before changing to a new one.
		CurrentState->End();
	}

	switch (InStateType)
	{
	case EActorStateType::Attack:
		CurrentState = MakeUnique<FAttackState>(OwnerActor);
		break;
	case EActorStateType::Patrol:
		CurrentState = MakeUnique<FPatrolState>(OwnerActor);
		break;
	case EActorStateType::MoveTo:
		CurrentState = MakeUnique<FMoveToState>(OwnerActor);
		break;
	case EActorStateType::SpeakTo:
		CurrentState = MakeUnique<FSpeakToState>(OwnerActor);
		break;
	case EActorStateType::Idle:
		CurrentState = MakeUnique<FIdleState>(OwnerActor);
		break;
	}

	if (CurrentState.IsValid())
	{
		CurrentStateType = InStateType;
		CurrentState->Start();
	}
	else
	{
		// Handle the case where the state could not be created.
		UE_LOG(LogTemp, Warning, TEXT("Failed to change state to %s"), *UWUtils::EnumToString(InStateType));
	}

}

void FUWActorStateMachine::Tick(float DeltaTime)
{
	if (CurrentState.IsValid())
	{
		CurrentState->Tick(DeltaTime);
	}
}
