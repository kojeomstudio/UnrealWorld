// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/// <summary>
/// LLMCommand <--> AICommand
/// </summary>
UENUM(BlueprintType)
enum class ELLMCommandType : uint8
{
	Unknown     UMETA(DisplayName = "Unknown"),
	MoveTo      UMETA(DisplayName = "Move To"),
	Attack      UMETA(DisplayName = "Attack"),
	PlayAnimation UMETA(DisplayName = "Play Animation"),
	Speak       UMETA(DisplayName = "Speak"),
	Patrol       UMETA(DisplayName = "Patrol"),
};

