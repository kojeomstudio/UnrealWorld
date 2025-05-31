// Fill out your copyright notice in the Description page of Project Settings.


#include "UWActorBase.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"

// Sets default values
AUWActorBase::AUWActorBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUWActorBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentStateType = EActorStateType::Idle;
}

// Called every frame
void AUWActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUWActorBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUWActorBase::ChangeState(EActorStateType InStateType)
{
	CurrentStateType = InStateType;
}

