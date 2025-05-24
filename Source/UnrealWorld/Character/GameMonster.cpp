// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMonster.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"

// Sets default values
AGameMonster::AGameMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainSkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MainSkeletalMeshComp"));

	SubParts_000 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SubSkeletalMeshComp_Parts000"));
	SubParts_001 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SubSkeletalMeshComp_Parts001"));
	SubParts_World = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SubSkeletalMeshComp_PartsWorld"));
	SubParts_Lower = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SubSkeletalMeshComp_PartsLower"));

	SubParts_000->SetupAttachment(MainSkeletalMeshComp, AttachSocketName);
	SubParts_001->SetupAttachment(MainSkeletalMeshComp, AttachSocketName);
	SubParts_World->SetupAttachment(MainSkeletalMeshComp, AttachSocketName);

	SubParts_Lower->SetupAttachment(MainSkeletalMeshComp);

	//SubParts_Lower->SetUsingAbsoluteLocation(true);
	SubParts_Lower->SetUsingAbsoluteRotation(true);
}

// Called when the game starts or when spawned
void AGameMonster::BeginPlay()
{
	Super::BeginPlay();
	
	FAttachmentTransformRules SubPartsRules_World = FAttachmentTransformRules
	(
		EAttachmentRule::KeepWorld,
		EAttachmentRule::KeepWorld,
		EAttachmentRule::KeepWorld,
		false
	);

	FAttachmentTransformRules SubPartsRules_Relative = FAttachmentTransformRules
	(
		EAttachmentRule::KeepRelative,
		EAttachmentRule::KeepRelative,
		EAttachmentRule::KeepWorld,
		false
	);

	FAttachmentTransformRules SubPartsRules_Snap = FAttachmentTransformRules
	(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		false
	);

	FAttachmentTransformRules SubPartsRules_Custom = FAttachmentTransformRules
	(
		EAttachmentRule::KeepRelative,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		false
	);

	SubParts_000->AttachToComponent(GetMainSkelMeshComp(), SubPartsRules_Relative, AttachSocketName);
	SubParts_001->AttachToComponent(GetMainSkelMeshComp(), SubPartsRules_Snap, AttachSocketName);
	SubParts_World->AttachToComponent(GetMainSkelMeshComp(), SubPartsRules_World, AttachSocketName);

	SubParts_Lower->AttachToComponent(GetMainSkelMeshComp(), SubPartsRules_Custom);

	//FRotator Rotator;
	//Rotator.RotateVector(FVector::ZeroVector);
}

// Called every frame
void AGameMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

