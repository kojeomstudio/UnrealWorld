// Fill out your copyright notice in the Description page of Project Settings.


#include "UWPlayerSpectator.h"
#include "UnrealWorld/GameMode/UnrealWorldInGameMode.h"
#include "UnrealWorld/Manager/UWGameCameraManager.h"
#include "UnrealWorld/UWPlayerController.h"

#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"

AUWPlayerSpectator::AUWPlayerSpectator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = 500.0f;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}
 
// Called when the game starts or when spawned
void AUWPlayerSpectator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AUWPlayerSpectator::Tick(float DeltaTime)
{

}

// Called to bind functionality to input
void AUWPlayerSpectator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AUWPlayerSpectator::OnMoveForward);
	InputComponent->BindAxis("MoveRight", this, &AUWPlayerSpectator::OnMoveRight);
}

void AUWPlayerSpectator::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

void AUWPlayerSpectator::OnMoveForward(float Value)
{
	if (Value != 0.0f)
	{
		
	}
}

void AUWPlayerSpectator::OnMoveRight(float Value)
{
	if (Value != 0.0f)
	{
		
	}
}