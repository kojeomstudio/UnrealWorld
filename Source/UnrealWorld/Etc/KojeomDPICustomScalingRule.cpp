// Fill out your copyright notice in the Description page of Project Settings.


#include "KojeomDPICustomScalingRule.h"

static FVector2D DefaultScreenSize = FVector2D(1600.0f, 900.0f);
static constexpr float DefaultScreenAspectRaito = 1600.0f / 900.0f;

float UKojeomDPICustomScalingRule::GetDPIScaleBasedOnSize(FIntPoint InSize) const
{
	float CurrentSizeX = static_cast<float>(InSize.X);
	float CurrentSizeY = static_cast<float>(InSize.Y);

	float CurrentAspectRatio = CurrentSizeX / CurrentSizeY;

	float ResultScale = CurrentSizeX / DefaultScreenAspectRaito;

	//
	if (CurrentAspectRatio > DefaultScreenAspectRaito)
	{
		float BasedSizeX = (CurrentSizeX * DefaultScreenAspectRaito) / CurrentAspectRatio;
		ResultScale = BasedSizeX / DefaultScreenSize.X;
	}
		
    return ResultScale;
}
