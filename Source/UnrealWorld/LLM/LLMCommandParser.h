#pragma once

#include "CoreMinimal.h"

class FLLMCommand;
class FBaseAICommand;

class FLLMCommandParser
{
public:
	FLLMCommandParser() = default;
	~FLLMCommandParser() = default;

public:
	// Parses JSON string into FLLMCommand
	bool Parse(const FString& JsonText, FLLMCommand& OutCommand);

public:
	TSharedPtr<FBaseAICommand> ParseToCommandObject(const FString& JsonText);
};
