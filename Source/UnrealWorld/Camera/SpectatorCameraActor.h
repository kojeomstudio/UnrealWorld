// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Camera/CameraActor.h"
#include "SpectatorCameraActor.generated.h"

class USpringArmComponent;

UCLASS()
class UNREALWORLD_API ASpectatorCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpectatorCameraActor();

};
