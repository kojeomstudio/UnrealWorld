#pragma once

#include "CoreMinimal.h"

#include "UnrealWorld/Common/UWEnums.h"

enum class ELLMCommandType : uint8;

class FLLMCommand
{
public:
	FLLMCommand() = default;
	~FLLMCommand() = default;

	
public:
	void Make(ELLMCommandType InCommandType, const FString& InTarget);

public:

	bool IsValid() const
	{
		return CommandType != ELLMCommandType::Unknown;
	}

	ELLMCommandType GetCommandType() const
	{
		return CommandType;
	}

	const FString& GetTarget() const
	{
		return Target;
	}


private:
	ELLMCommandType CommandType = ELLMCommandType::Unknown;
	FString Target;
};

