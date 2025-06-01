// Fill out your copyright notice in the Description page of Project Settings.


#include "UWActorBase.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/AIModule/Classes/BrainComponent.h"
#include "UnrealWorld/AI/UWAIController.h"

// Sets default values
AUWActorBase::AUWActorBase(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    USkeletalMeshComponent* SkeletalMesh = GetMesh();
    if (SkeletalMesh)
    {
        SkeletalMeshComponent = SkeletalMesh;
        UE_LOG(LogTemp, Log, TEXT("SkeletalMeshComponent successfully retrieved."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SkeletalMeshComponent is null."));
    }

    //
	StateMachine = MakeUnique<FUWActorStateMachine>(this);
}

// Called when the game starts or when spawned
void AUWActorBase::BeginPlay()
{
	Super::BeginPlay();

	if (AUWAIController* AIController = Cast<AUWAIController>(GetController()))
	{
		if (UBrainComponent* BrainComp = AIController->GetBrainComponent())
		{
			BrainComp->StartLogic();
		}
	}
}

// Called every frame
void AUWActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (StateMachine.IsValid())
    {
        StateMachine->Tick(DeltaTime);
    }
}

// Called to bind functionality to input
void AUWActorBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AUWActorBase::ChangeState(EActorStateType InStateType)
{
    if (StateMachine.IsValid()) 
    {
        StateMachine->ChangeState(InStateType);
    }
}

void AUWActorBase::PlayAnimation(const EActorAnimType InAnimType)
{
	UAnimSequenceBase* AnimSequence = nullptr;
    switch (InAnimType)
    {
	case EActorAnimType::Idle:
        AnimSequence = AnimationData.IdleAnim;
		break;
	case EActorAnimType::Walk:
		AnimSequence = AnimationData.WalkAnim;
		break;
	case EActorAnimType::Run:
		AnimSequence = AnimationData.RunAnim;
		break;
	case EActorAnimType::Attack:
		AnimSequence = AnimationData.AttackAnim;
		break;
    }
    PlayAnimation(AnimSequence);
}

void AUWActorBase::PlayAnimation(UAnimSequenceBase* InAnimSequence, const float InRate /*= 1.0f*/)
{
    if ((SkeletalMeshComponent == nullptr)|| (InAnimSequence ==nullptr))
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid SkeletalMesh or AnimSequence"));
        return;
    }

    UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
    if (AnimInstance == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("No AnimInstance found on SkeletalMesh"));
        return;
    }

    UAnimMontage* TempMontage = UAnimMontage::CreateSlotAnimationAsDynamicMontage(
        InAnimSequence,
        FName("DefaultSlot"), // (anim bp에서 default slot 설정 필요)
        0.0f,
        0.2f,
        InRate,
        9999                    
    );

    if (TempMontage == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to create dynamic montage"));
        return;
    }

    // Montage
    float Duration = AnimInstance->Montage_Play(TempMontage, InRate);
    if (Duration <= 0.f)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to play montage"));
    }
}

