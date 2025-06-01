// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UWEnums.generated.h"

/// <summary>
/// LLMCommand <--> AICommand <--> ActorState
/// </summary>
UENUM(BlueprintType)
enum class EActorStateType : uint8
{
	Unknown     UMETA(DisplayName = "Unknown"),
	MoveTo      UMETA(DisplayName = "MoveTo"),
	Attack      UMETA(DisplayName = "Attack"),
	SpeakTo     UMETA(DisplayName = "SpeakTo"),
	Patrol      UMETA(DisplayName = "Patrol"),
	Idle		UMETA(DisplayName = "Idle"),
};


/// <summary>
/// Actor Class Type
/// </summary>
UENUM(BlueprintType)
enum class EActorClassType : uint8
{
	Novice, // 모험가(디폴트 직업)
	Fighter, // 전사
	Ranger, // 원거리 딜러(궁수)
	Mage, // 마법사
	Healer // 힐러
};

/// <summary>
/// Actor Animation Type
/// </summary>
UENUM(BlueprintType)
enum class EActorAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Attack
};