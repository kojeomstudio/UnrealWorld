// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestPlugin.h"
#include "KojeomPlugin.h"


#define LOCTEXT_NAMESPACE "FTestPluginModule"

void FTestPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FTestPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FTestPluginModule::TestPluginFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("FTestPluginModule::TestPluginFunction()"));
}

void FTestPluginModule::CallKojeomPluginFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("FTestPluginModule::CallKojeomPluginFunction()"));

	if (FKojeomPluginModule* KojeomModule = static_cast<FKojeomPluginModule*>(FModuleManager::Get().LoadModule(TEXT("KojeomPlugin"))))
	{
		KojeomModule->TestFunction();
	}
}



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTestPluginModule, TestPlugin)