// GameConfigManager.cpp
#include "UWGameConfigManager.h"
#include "Misc/ConfigCacheIni.h"

const FString FGameConfigManager::DefaultGame_IniFile = GGameIni;

FString FGameConfigManager::GetStringValue(const FString& Section, const FString& Key, const FString& DefaultValue)
{
	FString Result;
	if (GConfig->GetString(*Section, *Key, Result, DefaultGame_IniFile))
	{
		return Result;
	}
	return DefaultValue;
}

void FGameConfigManager::SetStringValue(const FString& Section, const FString& Key, const FString& NewValue)
{
	GConfig->SetString(*Section, *Key, *NewValue, DefaultGame_IniFile);
	GConfig->Flush(false, DefaultGame_IniFile);
}

float FGameConfigManager::GetFloatValue(const FString& Section, const FString& Key, float DefaultValue)
{
	float Result;
	if (GConfig->GetFloat(*Section, *Key, Result, DefaultGame_IniFile))
	{
		return Result;
	}
	return DefaultValue;
}

void FGameConfigManager::SetFloatValue(const FString& Section, const FString& Key, float NewValue)
{
	GConfig->SetFloat(*Section, *Key, NewValue, DefaultGame_IniFile);
	GConfig->Flush(false, DefaultGame_IniFile);
}

int32 FGameConfigManager::GetIntValue(const FString& Section, const FString& Key, int32 DefaultValue)
{
	int32 Result;
	if (GConfig->GetInt(*Section, *Key, Result, DefaultGame_IniFile))
	{
		return Result;
	}
	return DefaultValue;
}

void FGameConfigManager::SetIntValue(const FString& Section, const FString& Key, int32 NewValue)
{
	GConfig->SetInt(*Section, *Key, NewValue, DefaultGame_IniFile);
	GConfig->Flush(false, DefaultGame_IniFile);
}

void FGameConfigManager::ReloadConfig()
{
	//FString ConfigFilePath = FPaths::Combine(FPaths::ProjectConfigDir(), TEXT("DefaultGame.ini"));

	if (GConfig)
	{
		UE_LOG(LogTemp, Log, TEXT("Reloading config file: %s"), *DefaultGame_IniFile);

		GConfig->UnloadFile(DefaultGame_IniFile);
		GConfig->LoadFile(DefaultGame_IniFile);
	}
}
