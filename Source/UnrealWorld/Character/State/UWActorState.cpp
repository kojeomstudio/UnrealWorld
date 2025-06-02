// Fill out your copyright notice in the Description page of Project Settings.


#include "UWActorState.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/AIModule/Classes/BrainComponent.h"

#include "UnrealWorld/Character/UWActorBase.h"
#include "UnrealWorld/AI/UWAIController.h"

#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Runtime/NavigationSystem/Public/NavigationData.h"
#include "Runtime/NavigationSystem/Public/NavigationSystemTypes.h"

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
	//https://dev.epicgames.com/documentation/ko-kr/unreal-engine/basic-navigation-in-unreal-engine

	if (OwnerActor == nullptr)
	{
		return;
	}

	// Play walk animation
	OwnerActor->PlayAnimation(EActorAnimType::Walk);

	// Clear existing patrol points
	PatrolPoints.Empty();

	const FVector Center = OwnerActor->GetActorLocation();
	const int32 NumPoints = 6;
	const float BaseRadius = 400.0f;
	const float RadiusStep = 300.0f;

	UWorld* World = OwnerActor->GetWorld();
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(World);

	if (NavSys == nullptr)
	{
		return;
	}

	// Generate patrol points in concentric circular pattern
	for (int32 Index = 0; Index < NumPoints; ++Index)
	{
		const float AngleDeg = FMath::FRandRange(0.0f, 360.0f);
		const float Radius = BaseRadius + (Index % 2) * RadiusStep;

		const FVector Offset = FVector(
			FMath::Cos(FMath::DegreesToRadians(AngleDeg)) * Radius,
			FMath::Sin(FMath::DegreesToRadians(AngleDeg)) * Radius,
			0.0f
		);

		const FVector Candidate = Center + Offset;

		FNavLocation Projected;
		if (NavSys->ProjectPointToNavigation(Candidate, Projected) == true)
		{
			PatrolPoints.Add(Projected.Location);
		}
	}

	CurrentTargetIndex = 0;
	MoveToCurrentTarget();
}

void FPatrolState::Tick(float DeltaTime)
{
	if (OwnerActor == nullptr)
	{
		return;
	}

	if (PatrolPoints.Num() == 0)
	{
		return;
	}

	const FVector CurrentLoc = OwnerActor->GetActorLocation();
	const FVector TargetLoc = PatrolPoints[CurrentTargetIndex];
	const float Distance = FVector::Dist2D(CurrentLoc, TargetLoc);
	const float Threshold = 100.0f;

	if (Distance < Threshold)
	{
		CurrentTargetIndex = (CurrentTargetIndex + 1) % PatrolPoints.Num();
		MoveToCurrentTarget();
	}
}

void FPatrolState::End()
{
}

void FPatrolState::MoveToCurrentTarget()
{
	if (OwnerActor == nullptr)
	{
		return;
	}

	if (PatrolPoints.IsValidIndex(CurrentTargetIndex) == false)
	{
		return;
	}

	const FVector Target = PatrolPoints[CurrentTargetIndex];

	FNavPathSharedPtr OutPath;
	OwnerActor->MoveToLocation(Target, &OutPath);
}

void FMoveToState::Start()
{
	if (OwnerActor != nullptr)
	{
		OwnerActor->PlayAnimation(EActorAnimType::Run);
	}

	const FVector Center = OwnerActor->GetActorLocation();
	const float BaseRadius = 700.0f;

	UWorld* World = OwnerActor->GetWorld();
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(World);

	if (NavSys == nullptr)
	{
		return;
	}

	FRandomStream RandomStream;
	RandomStream.GenerateNewSeed();

	const float AngleDeg = RandomStream.FRandRange(0.0f, 360.0f);

	const FVector Offset = FVector(
		FMath::Cos(FMath::DegreesToRadians(AngleDeg)) * BaseRadius,
		FMath::Sin(FMath::DegreesToRadians(AngleDeg)) * BaseRadius,
		0.0f
	);

	const FVector MoveToPosition = Center + Offset;

	FNavLocation Projected;
	if (NavSys->ProjectPointToNavigation(MoveToPosition, Projected) == true)
	{
		FNavPathSharedPtr OutPath;
		OwnerActor->MoveToLocation(Projected.Location, &OutPath);

#if WITH_EDITOR
		DrawDebugLine(
			OwnerActor->GetWorld(),
			OwnerActor->GetActorLocation(),
			Projected.Location,
			FColor::Green,
			false,      // 영구 여부 (false면 일정 시간 후 사라짐)
			10.0f,       // 지속 시간
			0,          // Depth Priority
			2.0f        // 선 굵기
		);

		DrawDebugSphere(
			OwnerActor->GetWorld(),
			Projected.Location,
			30.0f,        // 반지름
			12,           // 세그먼트 수
			FColor::Yellow,
			false,
			10.0f
		);
#endif
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
