#pragma once

#include "CoreMinimal.h"

class FLLMCommand;
class FBaseAICommand;

class FLLMCommandParser
{
public:
	FLLMCommandParser() = default;
	~FLLMCommandParser();

public:
	// Parses JSON string into FLLMCommand
	bool Parse(const FString& JsonText, TArray<FLLMCommand>& OutCommands);
};
