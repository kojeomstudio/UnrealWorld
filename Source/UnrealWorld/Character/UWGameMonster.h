// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealWorld/Character/UWActorBase.h"
#include "UWGameMonster.generated.h"

class USkeletalMeshComponent;

UCLASS()
class UNREALWORLD_API AUWGameMonster : public AUWActorBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUWGameMonster();

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
	TObjectPtr<USkeletalMeshComponent> SubParts_000;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> SubParts_001;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> SubParts_World;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> SubParts_Lower;

	UPROPERTY(EditAnywhere)
	FName AttachSocketName;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> MainSkeletalMeshComp;
};
