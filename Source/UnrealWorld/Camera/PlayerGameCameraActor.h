// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Camera/CameraActor.h"
#include "UWCameraActorBase.h"
#include "PlayerGameCameraActor.generated.h"

class USpringArmComponent;

UCLASS()
class UNREALWORLD_API APlayerGameCameraActor : public AUWCameraActorBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerGameCameraActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void Init();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
