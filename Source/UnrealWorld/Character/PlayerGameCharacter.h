// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "PlayerGameCharacter.generated.h"

UCLASS()
class UNREALWORLD_API APlayerGameCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	

public:
	APlayerGameCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

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

	void OnTouchPressed(ETouchIndex::Type InIndex, FVector InLocation);
	void OnTouchRepeated(ETouchIndex::Type InIndex, FVector InLocation);
	void OnTouchReleased(ETouchIndex::Type InIndex, FVector InLocation);

protected:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed;

protected:
	
};
