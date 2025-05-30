#pragma once

#include "CoreMinimal.h"

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
    static FString BuildUserPrompt(const TArray<TPair<FString, FString>>& ActorNameAndStateList);
};
