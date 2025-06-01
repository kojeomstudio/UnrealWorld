#pragma once

#include "CoreMinimal.h"

struct FPromptActorInfo
{
public:
	FString UniqueId; // Actor's unique identifier (or name)
	FString State; // Actor's current state
	FString Class; // Actor's class type (e.g., Fighter, Mage, etc.)

public:
	FPromptActorInfo(const FString& InUniqueId, const FString& InState, const FString& InClass)
		: UniqueId(InUniqueId), State(InState), Class(InClass)
	{
	}
};

/**
 * Utility class for building system and user prompts for local LLM (Ollama).
 */
class FGameWorldContextPrompt
{
public:
    static FString GetSystemPrompt();

    // Builds the formatted user prompt with numbered actor names and states
    // key : actor unique-id(or name)
    // key : actor state
    static FString BuildUserPrompt(const TArray<FPromptActorInfo>& InActorInfos);
};
