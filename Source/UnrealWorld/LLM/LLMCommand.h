#pragma once

#include "CoreMinimal.h"

#include "UnrealWorld/Common/UWEnums.h"

enum class EActorStateType : uint8;

class FLLMCommand
{
public:
	FLLMCommand() = default;
	~FLLMCommand() = default;

	
public:
	void Make(EActorStateType InCommandType, const FString& InTarget);

public:

	bool IsValid() const
	{
		return CommandType != EActorStateType::Unknown;
	}

	EActorStateType GetCommandType() const
	{
		return CommandType;
	}

	const FString& GetTarget() const
	{
		return Target;
	}


private:
	EActorStateType CommandType = EActorStateType::Unknown;
	FString Target;
};

