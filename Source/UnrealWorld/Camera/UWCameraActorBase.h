// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Camera/CameraActor.h"
#include "UWCameraActorBase.generated.h"

class USpringArmComponent;

UCLASS(Abstract)
class UNREALWORLD_API AUWCameraActorBase : public ACameraActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUWCameraActorBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	const FVector GetCameraToTargetDirection() const;
	const FRotator GetCameraRotation() const;

protected:
	void Follow();
	void LookAt();

protected:
	UPROPERTY(Category = PlayerCameraActor, EditAnyWhere)
	float Distance = 500.0f;

	UPROPERTY(Category = PlayerCameraActor, EditAnyWhere)
	float WheelScale = 1.0f;

	UPROPERTY(Category = PlayerCameraActor, EditAnyWhere)
	float MouseRotationScale = 1.0f;

	UPROPERTY(Category = PlayerCameraActor, EditAnyWhere)
	float MouseRotationSpeed = 50.0f;

	UPROPERTY(Category = PlayerCameraActor, EditAnyWhere)
	float Height = 500.0f;

	UPROPERTY(Category = PlayerCameraActor, EditAnyWhere)
	float MaxPitch = -60.0f;

	UPROPERTY(Category = PlayerCameraActor, EditAnyWhere)
	float MinPitch = -5.0f;


	UPROPERTY(Category = PlayerCameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(Transient)
	AActor* TargetActor = nullptr;
};
