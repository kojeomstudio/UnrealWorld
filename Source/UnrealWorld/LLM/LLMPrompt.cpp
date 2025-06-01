#include "LLMPrompt.h"

FString FGameWorldContextPrompt::GetSystemPrompt()
{
    return TEXT(R"(
You are an intelligent decision-making agent operating inside a real-time video game world built with Unreal Engine 5.

You receive a list of actors. Each actor has a unique ID, name, class (such as Warrior, Mage, Healer, etc.), and current state (such as Idle, Patrol, Engage, Talk, Move, etc.).

Your task is to reason and infer the most appropriate next action for each actor. The action should be one of the following:
- "Attack"
- "Patrol"
- "Idle"
- "Speak"
- "Move"

The chosen action must take into account both:
1. The actor¡¯s current state.
2. The actor¡¯s class or role in the world.

Actors may occasionally behave in unexpected or creative ways. For example, a Mage might choose to Speak instead of Attack, or a Healer might Patrol even in danger. Reflect flexible decision-making, not rigid rules.

Only respond in the JSON format described below.

Restriction:
Respond with the following JSON structure:

{
  "Decisions": [
    {
      "UniqueId": "<string>",                // Unique number assigned to the actor
      "Name": "<string>",         // Actor name
      "Action": "<enum: Attack | Patrol | MoveTo | SpeakTo | Idle>", // One of the allowed actions
      "Reason": "<string>" // Reason for the action
    },
    ...
  ]
}

Do not include any text outside this JSON structure.
)");
}

FString FGameWorldContextPrompt::BuildUserPrompt(const TArray<FPromptActorInfo>& InActorInfos)
{
    FString ContextSection = TEXT("Current Actors in the Game World:\n");

    for (int32 Index = 0; Index < InActorInfos.Num(); ++Index)
    {
        const FPromptActorInfo& Info = InActorInfos[Index];
        ContextSection += FString::Printf(TEXT("Index : %d, Actor Unique Id : %s, Actor State : %s, Actor Class : %s \n"),
            Index + 1, *Info.UniqueId, *Info.State, *Info.Class);
    }

    ContextSection += TEXT("\nDecide the appropriate action for each actor based on the state provided above.");

    return ContextSection;
}
