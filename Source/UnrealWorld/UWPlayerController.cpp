// Fill out your copyright notice in the Description page of Project Settings.


#include "UWPlayerController.h"

bool AUWPlayerController::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	Super::InputKey(Key, EventType, AmountDepressed, bGamepad);

    return false;
}

void AUWPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MouseWheel"), this, &AUWPlayerController::OnMouseWheel);
}

void AUWPlayerController::OnMouseWheel(float InAxisValue)
{
	if (FMath::IsNearlyEqual(InAxisValue, 0.0f) == false)
	{
		CachedMouseWheelAxisValue = InAxisValue;
	}
}
