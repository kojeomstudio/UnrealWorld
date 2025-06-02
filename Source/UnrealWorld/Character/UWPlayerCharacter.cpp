// Fill out your copyright notice in the Description page of Project Settings.

#include "UWPlayerCharacter.h"

#include "UnrealWorld/GameMode/UnrealWorldInGameMode.h"

#include "UnrealWorld/Common/UWEssentialHeaders.h"

#include "UnrealWorld/Manager/UWGameCameraManager.h"
#include "UnrealWorld/Manager/UWGameScreenTouchManager.h"

#include "UnrealWorld/Data/UWGameBPAsset.h"

#include "UnrealWorld/UWPlayerController.h"

AUWPlayerCharacter::AUWPlayerCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MoveSpeed = 500.0f;
}
 
// Called when the game starts or when spawned
void AUWPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//const FTransform& Transform = GetTransform();
	//Transform.GetLocation();
}

// Called every frame
void AUWPlayerCharacter::Tick(float DeltaTime)
{

}

// Called to bind functionality to input
void AUWPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis(TEXT("MoveForward"), this, &AUWPlayerCharacter::OnMoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AUWPlayerCharacter::OnMoveRight);

	InputComponent->BindTouch(IE_Pressed, this, &AUWPlayerCharacter::OnTouchPressed);
	InputComponent->BindTouch(IE_Repeat, this, &AUWPlayerCharacter::OnTouchRepeated);
	InputComponent->BindTouch(IE_Released, this, &AUWPlayerCharacter::OnTouchReleased);
}

void AUWPlayerCharacter::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

void AUWPlayerCharacter::OnMoveForward(float Value)
{
	if (FMath::IsNearlyZero(Value))
	{
		return;
	}

	FVector Direction = FRotationMatrix(UW::Get<UUWGameCameraManager>().GetCameraRotation()).GetScaledAxis(EAxis::X);
	Direction.Z = 0.0f;
	Direction.Normalize();

	AddMovementInput(Direction, Value * MoveSpeed * GetWorld()->GetDeltaSeconds());

	FVector FacingDirection = Direction;
	if (Value < 0.0f)
	{
		FacingDirection *= -1.0f;
	}

	FRotator TargetRotation = FacingDirection.Rotation();
	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 10.0f);

	SetActorRotation(NewRotation);
}

void AUWPlayerCharacter::OnMoveRight(float Value)
{
	if (FMath::IsNearlyZero(Value))
	{
		return;
	}

	FVector Direction = FRotationMatrix(UW::Get<UUWGameCameraManager>().GetCameraRotation()).GetScaledAxis(EAxis::Y);
	Direction.Z = 0.0f;
	Direction.Normalize();

	AddMovementInput(Direction, Value * MoveSpeed * GetWorld()->GetDeltaSeconds());

	FVector FacingDirection = Direction;
	if (Value < 0.0f)
	{
		FacingDirection *= -1.0f;
	}

	FRotator TargetRotation = FacingDirection.Rotation();
	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 10.0f);

	SetActorRotation(NewRotation);
}


void AUWPlayerCharacter::OnTouchPressed(ETouchIndex::Type InIndex, FVector InLocation)
{
	UW::Get<UUWGameScreenTouchManager>().OnTouchPressed(InIndex, InLocation);
}

void AUWPlayerCharacter::OnTouchRepeated(ETouchIndex::Type InIndex, FVector InLocation)
{
	UW::Get<UUWGameScreenTouchManager>().OnTouchRepeated(InIndex, InLocation);
}

void AUWPlayerCharacter::OnTouchReleased(ETouchIndex::Type InIndex, FVector InLocation)
{
	UW::Get<UUWGameScreenTouchManager>().OnTouchReleased(InIndex, InLocation);
}
