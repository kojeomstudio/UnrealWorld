// Copyright Epic Games, Inc. All Rights Reserved.

#include "KojeomPlugin.h"


#define LOCTEXT_NAMESPACE "FKojeomPluginModule"

void FKojeomPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FKojeomPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FKojeomPluginModule::KojeomPluginFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("FKojeomPluginModule::KojeomPluginFunction()"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FKojeomPluginModule, KojeomPlugin)