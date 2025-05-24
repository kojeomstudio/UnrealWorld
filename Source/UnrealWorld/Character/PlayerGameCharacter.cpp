// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerGameCharacter.h"

#include "UnrealWorld/GameMode/UnrealWorldInGameMode.h"

#include "UnrealWorld/Common/UWEssentialHeaders.h"

#include "UnrealWorld/Manager/UWGameCameraManager.h"
#include "UnrealWorld/Manager/UWGameScreenTouchManager.h"

#include "UnrealWorld/Data/UWGameBPAsset.h"

#include "UnrealWorld/UWPlayerController.h"

APlayerGameCharacter::APlayerGameCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = 500.0f;
}
 
// Called when the game starts or when spawned
void APlayerGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	//const FTransform& Transform = GetTransform();
	//Transform.GetLocation();
}

// Called every frame
void APlayerGameCharacter::Tick(float DeltaTime)
{

}

// Called to bind functionality to input
void APlayerGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerGameCharacter::OnMoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerGameCharacter::OnMoveRight);

	InputComponent->BindTouch(IE_Pressed, this, &APlayerGameCharacter::OnTouchPressed);
	InputComponent->BindTouch(IE_Repeat, this, &APlayerGameCharacter::OnTouchRepeated);
	InputComponent->BindTouch(IE_Released, this, &APlayerGameCharacter::OnTouchReleased);
}

void APlayerGameCharacter::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

void APlayerGameCharacter::OnMoveForward(float Value)
{
	if (Value != 0.0f)
	{
		FVector Direction = FRotationMatrix(UW::Get<UUWGameCameraManager>().GetCameraRotation()).GetScaledAxis(EAxis::X);
		Direction.Z = 0.0f;

		AddMovementInput(Direction, Value * MoveSpeed * GetWorld()->GetDeltaSeconds());

		if (Value < 0.0f)
		{
			Direction *= Value;
		}
		
		FRotator NewRotation = Direction.Rotation();
		SetActorRotation(FQuat::Slerp(GetActorRotation().Quaternion(), NewRotation.Quaternion(), 0.2f));
	}
}

void APlayerGameCharacter::OnMoveRight(float Value)
{
	if (Value != 0.0f)
	{
		FVector Direction = FRotationMatrix(UW::Get<UUWGameCameraManager>().GetCameraRotation()).GetScaledAxis(EAxis::Y);
		Direction.Z = 0.0f;

		AddMovementInput(Direction, Value * MoveSpeed * GetWorld()->GetDeltaSeconds());

		if (Value < 0.0f)
		{
			Direction *= Value;
		}

		FRotator NewRotation = Direction.Rotation();
		SetActorRotation(FQuat::Slerp(GetActorRotation().Quaternion(), NewRotation.Quaternion(), 0.2f));
	}
}

void APlayerGameCharacter::OnTouchPressed(ETouchIndex::Type InIndex, FVector InLocation)
{
	UW::Get<UUWGameScreenTouchManager>().OnTouchPressed(InIndex, InLocation);
}

void APlayerGameCharacter::OnTouchRepeated(ETouchIndex::Type InIndex, FVector InLocation)
{
	UW::Get<UUWGameScreenTouchManager>().OnTouchRepeated(InIndex, InLocation);
}

void APlayerGameCharacter::OnTouchReleased(ETouchIndex::Type InIndex, FVector InLocation)
{
	UW::Get<UUWGameScreenTouchManager>().OnTouchReleased(InIndex, InLocation);
}
