// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class KOJEOMPLUGIN_API FKojeomPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void KojeomPluginFunction();

public:
	void TestFunction()
	{
		UE_LOG(LogTemp, Warning, TEXT("FKojeomPluginModule::TestFunction( Value : %s)"), *FString::FromInt(TestValue));
	}

private:
	int32 TestValue = 9999;
};
