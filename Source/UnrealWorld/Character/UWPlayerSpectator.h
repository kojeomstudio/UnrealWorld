// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "UWPlayerSpectator.generated.h"

UCLASS()
class UNREALWORLD_API AUWPlayerSpectator : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	AUWPlayerSpectator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Serialize(FArchive& Ar) override;

protected:
	void OnMoveForward(float Value);
	void OnMoveRight(float Value);

protected:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed;

private:
	UPROPERTY(Transient)
	TObjectPtr<class UCameraComponent> CameraComponent;

	UPROPERTY(Transient)
	TObjectPtr<class USpringArmComponent> SpringArmComponent;

};
