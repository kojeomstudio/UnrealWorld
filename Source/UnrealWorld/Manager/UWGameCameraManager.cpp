// Fill out your copyright notice in the Description page of Project Settings.


#include "UWGameCameraManager.h"

#include "Runtime/Engine/Classes/Camera/CameraActor.h"
#include "Runtime/Engine/Classes/Engine/World.h"

#include "UnrealWorld/Camera/PlayerGameCameraActor.h"

void UUWGameCameraManager::Init()
{
}

void UUWGameCameraManager::Tick(float InDeltaTime)
{
}

void UUWGameCameraManager::Release()
{
}

const FVector UUWGameCameraManager::GetCameraDirection() const
{
	if (PlayerCameraActor)
	{
		return PlayerCameraActor->GetCameraToTargetDirection();
	}
	return FVector::ZeroVector;
}

const FRotator UUWGameCameraManager::GetCameraRotation() const
{
	if (PlayerCameraActor)
	{
		return PlayerCameraActor->GetCameraRotation();
	}
	return FRotator::ZeroRotator;
}

void UUWGameCameraManager::SpawnCamera(const FGameCameraInitParams& InInitParams)
{
	if (UWorld* World = GetWorld())
	{
		PlayerCameraActor = World->SpawnActor<APlayerGameCameraActor>
		(
			InInitParams.GetActorClass(),
			InInitParams.GetSpawnTransform()
		);

		if (PlayerCameraActor)
		{
			PlayerCameraActor->Init();
		}
	}
}
