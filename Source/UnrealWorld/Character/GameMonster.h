// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameMonster.generated.h"

class USkeletalMeshComponent;

UCLASS()
class UNREALWORLD_API AGameMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	USkeletalMeshComponent* GetMainSkelMeshComp() { return MainSkeletalMeshComp; }

protected:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SubParts_000;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SubParts_001;
	
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SubParts_World;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SubParts_Lower;

	UPROPERTY(EditAnywhere)
	FName AttachSocketName;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* MainSkeletalMeshComp;
};
