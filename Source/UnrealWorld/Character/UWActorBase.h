// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "UnrealWorld/Character/State/UWActorStateMachine.h"
#include "UnrealWorld/Common/UWEnums.h"

#include "UWActorBase.generated.h"

class USkeletalMeshComponent;
class UAnimSequence;
class UAnimSequenceBase;

USTRUCT()
struct FActorAnimationData
{
	GENERATED_BODY()

public:
	FActorAnimationData() = default;
	FActorAnimationData(UAnimSequenceBase* InIdleAnim, UAnimSequenceBase* InWalkAnim, UAnimSequenceBase* InRunAnim, UAnimSequenceBase* InAttackAnim)
		: IdleAnim(InIdleAnim), WalkAnim(InWalkAnim), RunAnim(InRunAnim), AttackAnim(InAttackAnim)
	{
	}

public:
	UPROPERTY(Transient)
	TObjectPtr<UAnimSequenceBase> IdleAnim;

	UPROPERTY(Transient)
	TObjectPtr<UAnimSequenceBase> WalkAnim;

	UPROPERTY(Transient)
	TObjectPtr<UAnimSequenceBase> RunAnim;

	UPROPERTY(Transient)
	TObjectPtr<UAnimSequenceBase> AttackAnim;
};

UCLASS()
class UNREALWORLD_API AUWActorBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUWActorBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION(BlueprintCallable, Category = "UWActorBase")
	void ChangeState(EActorStateType InStateType);

	void PlayAnimation(const EActorAnimType InAnimType);
	void PlayAnimation(UAnimSequenceBase* InAnimSequence, const float InRate = 1.0f);

	// setters.
public:
	void SetGuId(const FGuid& InGuid)
	{
		Id = InGuid;
	}

	void SetClass(const EActorClassType InClass)
	{
		ActorClassType = InClass;
	}

	void SetAnimationData(const FActorAnimationData& InAnimationData)
	{
		AnimationData = InAnimationData;
	}

	// getters.
public:

	UFUNCTION(BlueprintCallable, Category = "UWActorBase")
	const FGuid& GetGuId() const
	{
		return Id;
	}

	UFUNCTION(BlueprintCallable, Category = "UWActorBase")
	const EActorStateType GetStateType() const
	{
		if (StateMachine.IsValid())
		{
			return StateMachine->GetCurrentStateType();
		}
		return EActorStateType::Unknown;
	}

	UFUNCTION(BlueprintCallable, Category = "UWActorBase")
	const EActorClassType GetClassType() const
	{
		return ActorClassType;
	}

protected:
	FGuid Id;
	EActorClassType ActorClassType = EActorClassType::Novice;

	TUniquePtr<FUWActorStateMachine> StateMachine;
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent = nullptr;

	UPROPERTY(Transient)
	FActorAnimationData AnimationData;
};
