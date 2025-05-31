// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnrealWorld/Common/UWEnums.h"
#include "UWActorBase.generated.h"

class USkeletalMeshComponent;

UCLASS()
class UNREALWORLD_API AUWActorBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUWActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION(BlueprintCallable, Category = "UWActorBase_BP")
	void ChangeState(EActorStateType InStateType);

	// setters.
public:
	void SetGuId(const FGuid& InGuid)
	{
		Id = InGuid;
	}

	// getters.
public:

	UFUNCTION(BlueprintCallable, Category = "UWActorBase_BP")
	const FGuid& GetGuId()
	{
		return Id;
	}

	UFUNCTION(BlueprintCallable, Category = "UWActorBase_BP")
	const EActorStateType GetStateType()
	{
		return CurrentStateType;
	}

protected:
	FGuid Id;
	EActorStateType CurrentStateType = EActorStateType::Unknown;
};
