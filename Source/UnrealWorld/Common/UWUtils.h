#pragma once

#include "CoreMinimal.h"

class FScreenDebugHelper
{
public:
	static void Print(const FString& Message, float Duration = 2.0f, const FColor& Color = FColor::White, int32 Key = -1);
	static void Printf(float Duration, const FColor& Color, const TCHAR* Format, ...);
};
