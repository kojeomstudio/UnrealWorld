// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealWorld/Character/UWActorBase.h"
#include "UWGameNpc.generated.h"

class USkeletalMeshComponent;

UCLASS()
class UNREALWORLD_API AUWGameNpc : public AUWActorBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUWGameNpc();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	
};
