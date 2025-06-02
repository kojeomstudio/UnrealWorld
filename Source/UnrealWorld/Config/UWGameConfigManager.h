// GameConfigManager.h
#pragma once

#include "CoreMinimal.h"

class FGameConfigManager
{
public:
	static FString GetStringValue(const FString& Section, const FString& Key, const FString& DefaultValue = TEXT(""));

	static void SetStringValue(const FString& Section, const FString& Key, const FString& NewValue);

	static float GetFloatValue(const FString& Section, const FString& Key, float DefaultValue = 0.f);

	static void SetFloatValue(const FString& Section, const FString& Key, float NewValue);

	static int32 GetIntValue(const FString& Section, const FString& Key, int32 DefaultValue = 0);

	static void SetIntValue(const FString& Section, const FString& Key, int32 NewValue);

public:
	static void ReloadConfig();
	
private:
	static const FString DefaultGame_IniFile;  // DefaultGame.ini
};
