#include "LLMPrompt.h"

FString FGameWorldContextPrompt::GetSystemPrompt()
{
    return TEXT(R"(
You are an AI decision-making agent inside a video game world using Unreal Engine.

You receive a list of actors, each with a unique ID, name, and current state.

Based on the state of each actor, determine the most appropriate action: 
either "Attack", "Patrol", or "Move".

Only respond in the JSON format described below.

Restriction:
Respond with the following JSON structure:

{
  "Decisions": [
    {
      "UniqueId": "<string>",                // Unique number assigned to the actor
      "Name": "<string>",         // Actor name
      "Action": "<enum: Attack | Patrol | MoveTo | SpeakTo | Idle>" // One of the allowed actions
    },
    ...
  ]
}

Do not include any text outside this JSON structure.
)");
}

FString FGameWorldContextPrompt::BuildUserPrompt(const TArray<TPair<FString, FString>>& ActorNameAndStateList)
{
    FString ContextSection = TEXT("Current Actors in the Game World:\n");

    for (int32 Index = 0; Index < ActorNameAndStateList.Num(); ++Index)
    {
        const TPair<FString, FString>& Pair = ActorNameAndStateList[Index];
        ContextSection += FString::Printf(TEXT("Index : %d, Actor Unique Id : %s, Actor State : %s\n"), Index + 1, *Pair.Key, *Pair.Value);
    }

    ContextSection += TEXT("\nDecide the appropriate action for each actor based on the state provided above.");

    return ContextSection;
}


//
// example usage
//

//TArray<TPair<FString, FString>> Actors;
//Actors.Add({ TEXT("Enemy_01"), TEXT("Near player, hostile") });
//Actors.Add({ TEXT("Ally_01"), TEXT("Idle near base") });
//Actors.Add({ TEXT("PatrolBot_03"), TEXT("Walking route near gate") });
//
//FString SystemPrompt = FGameWorldContextPrompt::GetSystemPrompt();
//FString UserPrompt = FGameWorldContextPrompt::BuildUserPrompt(Actors);

// expectation result.
//{
//    "Decisions": [
//    {
//        "ID": 1,
//        "Name" : "Enemy_01",
//        "Action" : "Attack"
//    },
//    {
//      "ID": 2,
//      "Name" : "Ally_01",
//      "Action" : "Move"
//    },
//    {
//      "ID": 3,
//      "Name" : "PatrolBot_03",
//      "Action" : "Patrol"
//    }
//    ]
//}
