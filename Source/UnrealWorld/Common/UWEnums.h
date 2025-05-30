// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/// <summary>
/// LLMCommand <--> AICommand <--> ActorState
/// </summary>
UENUM(BlueprintType)
enum class ELLMCommandType : uint8
{
	Unknown     UMETA(DisplayName = "Unknown"),
	MoveTo      UMETA(DisplayName = "Move To"),
	Attack      UMETA(DisplayName = "Attack"),
	SpeakTo       UMETA(DisplayName = "SpeakTo"),
	Patrol       UMETA(DisplayName = "Patrol"),
	Idle UMETA(DisplayName = "Idle"),
};

