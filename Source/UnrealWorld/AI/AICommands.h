#pragma once

#include "CoreMinimal.h"
#include "UnrealWorld/Common/UWEnums.h"

class AAIController;

class FBaseAICommand
{
public:
	virtual ~FBaseAICommand() = default;
	virtual void Execute(AAIController* Controller) = 0;
};

class FMoveToCommand : public FBaseAICommand
{
public:
	explicit FMoveToCommand(const FString& InTarget) : Target(InTarget) {}

public:
	virtual void Execute(AAIController* Controller) override;

private:
	FString Target;
};

class FAttackCommand : public FBaseAICommand
{
public:
	explicit FAttackCommand(const FString& InTarget) : Target(InTarget) {}

public:
	virtual void Execute(AAIController* Controller) override;

private:
	FString Target;
};

class FPatrolCommand : public FBaseAICommand
{
public:
	explicit FPatrolCommand(const FString& InTarget) {}

public:
	virtual void Execute(AAIController* Controller) override;
};
