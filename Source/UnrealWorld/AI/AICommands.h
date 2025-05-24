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

	virtual void Execute(AAIController* Controller) override;

private:
	FString Target;
};
