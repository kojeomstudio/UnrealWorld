// GameConfigManager.cpp
#include "UWGameConfigManager.h"
#include "Misc/ConfigCacheIni.h"

const FString FGameConfigManager::IniFile = GGameIni;

FString FGameConfigManager::GetStringValue(const FString& Section, const FString& Key, const FString& DefaultValue)
{
	FString Result;
	if (GConfig->GetString(*Section, *Key, Result, IniFile))
	{
		return Result;
	}
	return DefaultValue;
}

void FGameConfigManager::SetStringValue(const FString& Section, const FString& Key, const FString& NewValue)
{
	GConfig->SetString(*Section, *Key, *NewValue, IniFile);
	GConfig->Flush(false, IniFile);
}

float FGameConfigManager::GetFloatValue(const FString& Section, const FString& Key, float DefaultValue)
{
	float Result;
	if (GConfig->GetFloat(*Section, *Key, Result, IniFile))
	{
		return Result;
	}
	return DefaultValue;
}

void FGameConfigManager::SetFloatValue(const FString& Section, const FString& Key, float NewValue)
{
	GConfig->SetFloat(*Section, *Key, NewValue, IniFile);
	GConfig->Flush(false, IniFile);
}

int32 FGameConfigManager::GetIntValue(const FString& Section, const FString& Key, int32 DefaultValue)
{
	int32 Result;
	if (GConfig->GetInt(*Section, *Key, Result, IniFile))
	{
		return Result;
	}
	return DefaultValue;
}

void FGameConfigManager::SetIntValue(const FString& Section, const FString& Key, int32 NewValue)
{
	GConfig->SetInt(*Section, *Key, NewValue, IniFile);
	GConfig->Flush(false, IniFile);
}
