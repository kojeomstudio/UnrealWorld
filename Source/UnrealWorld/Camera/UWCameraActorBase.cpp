// Fill out your copyright notice in the Description page of Project Settings.


#include "UWCameraActorBase.h"

#include "UnrealWorld/Common/UWEssentialHeaders.h"

#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"

#include "UnrealWorld/Character/PlayerGameCharacter.h"
#include "UnrealWorld/UWPlayerController.h"

#include "UnrealWorld/Manager/UWGameScreenTouchManager.h"

AUWCameraActorBase::AUWCameraActorBase(const FObjectInitializer& ObjectInitializer  /*= FObjectInitializer::Get()*/)
	: Super::ACameraActor(ObjectInitializer)
{
	// Set this actor to call Tick() every frame 
	PrimaryActorTick.bCanEverTick = true;

	// Create a spring arm component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = Distance;
	SpringArmComponent->bUsePawnControlRotation = true;

	GetCameraComponent()->SetupAttachment(SpringArmComponent);
}

void AUWCameraActorBase::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		PlayerController->SetViewTarget(this);
		TargetActor = PlayerController->GetPawn();
	}
}

void AUWCameraActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Follow();
	//LookAt();

	if (AUWPlayerController* PlayerController = UW::GetPlatformInstance()->GetMyController())
	{
		UUWGameScreenTouchManager& ScreenTouchManager = UW::Get<UUWGameScreenTouchManager>();

		if (FTouchInfo* TargetTouchInfo = ScreenTouchManager.FindTouchInfo(ETouchIndex::Type::Touch1))
		{
			float DeltaX = TargetTouchInfo->CurLocation.X - TargetTouchInfo->OldLocation.X;
			float DeltaY = TargetTouchInfo->CurLocation.Y - TargetTouchInfo->OldLocation.Y;

			FRotator OriginRot = GetActorRotation();

			FRotator TargetRot = GetActorRotation();
			TargetRot.Yaw += DeltaX;
			TargetRot.Pitch = FMath::Clamp(TargetRot.Pitch + DeltaY, MaxPitch, MinPitch);

			const FRotator NewRot = FMath::RInterpTo(OriginRot, TargetRot, DeltaTime, 10.0f);
			SetActorRotation(NewRot);
		}

		const float WheelValue = PlayerController->GetCachedMouseWheelAxisValue();
		SpringArmComponent->TargetArmLength = Distance + (WheelValue * WheelScale);
	}
}


void AUWCameraActorBase::Follow()
{
	if (TargetActor)
	{
		FVector TargetLocation = TargetActor->GetActorLocation();
		FVector ToTargetDirection = GetCameraToTargetDirection();

		FVector NewCameraLocation = TargetLocation - ToTargetDirection * SpringArmComponent->TargetArmLength;
		SetActorLocation(NewCameraLocation);
	}
}

void AUWCameraActorBase::LookAt()
{
	if (TargetActor)
	{
		FVector ToTargetDirection = GetCameraToTargetDirection();

		// X axis -> rolling(=forward), based on forward vector and then look at.
		FRotator LookAtRotation = FRotationMatrix::MakeFromX(ToTargetDirection).Rotator();
		SetActorRotation(LookAtRotation);
	}
}

const FVector AUWCameraActorBase::GetCameraToTargetDirection() const
{
	if (TargetActor)
	{
		FVector TargetLocation = TargetActor->GetActorLocation();
		FVector ToTargetDirection = TargetLocation - GetCameraComponent()->GetComponentLocation();
		ToTargetDirection.Normalize();

		return ToTargetDirection;
	}

	return FVector::ZeroVector;
}

const FRotator AUWCameraActorBase::GetCameraRotation() const
{
	return GetActorRotation();
}
