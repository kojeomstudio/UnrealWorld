// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameCameraActor.h"

#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"

#include "UnrealWorld/Character/UWPlayerCharacter.h"
#include "UnrealWorld/UWPlayerController.h"

#include "Runtime/Core/Public/Internationalization/Internationalization.h"

#define LOCTEXT_NAMESPACE "MyNamespace"

// Sets default values
APlayerGameCameraActor::APlayerGameCameraActor(const FObjectInitializer& ObjectInitializer /* = FObjectInitializer::Get()*/)
	: Super::AUWCameraActorBase(ObjectInitializer)
{
	
}

void APlayerGameCameraActor::Init()
{
}

// Called when the game starts or when spawned
void APlayerGameCameraActor::BeginPlay()
{
	Super::BeginPlay();
	if (TargetActor)
	{
		FVector Location = TargetActor->GetActorLocation();
		Location.Z += Height;

		SetActorLocation(Location);

		Follow();
		LookAt();
	}
}

// Called every frame
void APlayerGameCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


#undef LOCTEXT_NAMESPACE