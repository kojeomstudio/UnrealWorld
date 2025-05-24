// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UWPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALWORLD_API AUWPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	const float GetCachedMouseWheelAxisValue() const { return CachedMouseWheelAxisValue; }
	

protected:
	/** Handles a key press */
	virtual bool InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad);

	virtual void SetupInputComponent() override;

private:
	void OnMouseWheel(float InAxisValue);

private:
	float CachedMouseWheelAxisValue = 0.0f;
};
