// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnrealWorldPatchMode.h"
#include "Runtime/Online/HTTP/Public/HttpManager.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"
#include "Runtime/PakFile/Public/IPlatformFilePak.h"

#include "TestPlugin.h"

#include "UnrealWorld/Config/UWGameConfigManager.h"

FString PakContentPath = FPaths::ProjectContentDir() + TEXT("/Paks/");

void AUnrealWorldPatchMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UE_LOG(LogTemp, Log, TEXT("AUnrealWorldPatchMode::InitGame [MapName : %s]"), *MapName);

	FTestPluginModule& MyPluginModule = FModuleManager::LoadModuleChecked<FTestPluginModule>("TestPlugin");

	MyPluginModule.TestPluginFunction();
	MyPluginModule.CallKojeomPluginFunction();
}

void AUnrealWorldPatchMode::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);


}


void AUnrealWorldPatchMode::CPP_DownloadPakFile(const FString& InUrl)
{
	UE_LOG(LogTemp, Warning, TEXT("CPP_DownloadPakFile >>> Url : %s"), *InUrl);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &AUnrealWorldPatchMode::OnCompleteDownload);

	HttpRequest->SetURL(InUrl);
	HttpRequest->SetVerb("GET");

	HttpRequest->ProcessRequest();
}

void AUnrealWorldPatchMode::CPP_DownloadPakFile_FromCDN()
{
	FString Url;
#if (!UE_BUILD_SHIPPING)
	Url = FGameConfigManager::GetStringValue(FString(TEXT("CDN")), FString(TEXT("Dev")));
#else
	Url = FGameConfigManager::GetStringValue(FString(TEXT("CDN")), FString(TEXT("Live")));
#endif

	FString FormatString = TEXT("\\\\{0}\\cdn");

	TArray<FStringFormatArg> FormatArgs;
	FormatArgs.Add(Url);

	FString Result = FString::Format(*FormatString, FormatArgs);
	
	CPP_DownloadPakFile(Result);
}

void AUnrealWorldPatchMode::CPP_MountAllPakFile()
{
	MountProcess();
}

void AUnrealWorldPatchMode::OnCompleteDownload(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
    {
        TArray<uint8> Content = Response->GetContent();
        
		FString FileName = PakContentPath + TEXT("");
        if (FFileHelper::SaveArrayToFile(Content, *FileName))
        {
            UE_LOG(LogTemp, Warning, TEXT("Pak file downloaded successfully to %s"), *PakContentPath);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to save downloaded Pak file."));
        }
    }
}

void AUnrealWorldPatchMode::MountProcess()
{
	FString MountPoint = FPaths::ProjectContentDir();

	if (FPakPlatformFile* PakPlatformFile = (FPakPlatformFile*)FPlatformFileManager::Get().FindPlatformFile(FPakPlatformFile::GetTypeName()))
	{
		TArray<FString> OutPakFiles;
		//PakPlatformFile->FindPakFilesInDirectory(PakPlatformFile, *PakContentPath, TEXT(""), OutPakFiles);

		TArray<FString> MountedPakFileNames;
		PakPlatformFile->GetMountedPakFilenames(MountedPakFileNames);

		FString DebugMessage = FString::Printf(TEXT("Content pak path : %s OutPakFiles Num : %d MountedFiles Num : %d"), *PakContentPath, OutPakFiles.Num(), MountedPakFileNames.Num());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage);


		for (const FString& PakFilePath : OutPakFiles)
		{
			PakPlatformFile->Mount(*PakFilePath, 1, *PakContentPath);
		}
	}
}
