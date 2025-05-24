// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DPICustomScalingRule.h"
#include "KojeomDPICustomScalingRule.generated.h"

/**
 * 
 */
UCLASS()
class UNREALWORLD_API UKojeomDPICustomScalingRule : public UDPICustomScalingRule
{
	GENERATED_BODY()
	
public:
	virtual float GetDPIScaleBasedOnSize(FIntPoint InSize) const override;
};
