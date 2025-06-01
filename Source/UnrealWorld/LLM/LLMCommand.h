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
	void Make(EActorStateType InCommandType, const FString& InTarget, const FString& InUniqueId, const FString& InReason);

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

	const FString& GetUniqueId() const
	{
		return UniqueId;
	}

	const FString& GetReason() const
	{
		return Reason;
	}


private:
	EActorStateType CommandType = EActorStateType::Unknown;
	FString Target;
	FString UniqueId;
	FString Reason;
};

