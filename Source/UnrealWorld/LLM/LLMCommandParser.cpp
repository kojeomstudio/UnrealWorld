#include "LLMCommandParser.h"
#include "LLMCommand.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#include "UnrealWorld/Common/UWEnums.h"
#include "UnrealWorld/AI/AICommands.h"

EActorStateType StringToCommandType(const FString& InStr)
{
	if (InStr.Equals("MoveTo", ESearchCase::IgnoreCase))
	{
		return EActorStateType::MoveTo;
	}
	else if (InStr.Equals("Attack", ESearchCase::IgnoreCase))
	{
		return EActorStateType::Attack;
	}
	else if (InStr.Equals("SpeakTo", ESearchCase::IgnoreCase))
	{
		return EActorStateType::SpeakTo;
	}
	else if (InStr.Equals("Patrol", ESearchCase::IgnoreCase))
	{
		return EActorStateType::Patrol;
	}
	else if (InStr.Equals("Idle", ESearchCase::IgnoreCase))
	{
		return EActorStateType::Idle;
	}

	return EActorStateType::Unknown;
}

FLLMCommandParser::~FLLMCommandParser()
{
	// to do
}

bool FLLMCommandParser::Parse(const FString& JsonText, TArray<FLLMCommand>& OutCommands)
{
    TSharedPtr<FJsonObject> RootObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonText);

    if (FJsonSerializer::Deserialize(Reader, RootObject) == false || RootObject.IsValid() == false)
    {
        return false; // JSON 파싱 실패
    }

    const TArray<TSharedPtr<FJsonValue>>* DecisionsArray;
    if (RootObject->TryGetArrayField(TEXT("Decisions"), DecisionsArray) == false)
    {
        return false; // "Decisions" 필드 없음
    }

    for (const TSharedPtr<FJsonValue>& ItemValue : *DecisionsArray)
    {
        const TSharedPtr<FJsonObject>* ItemObject;
        if (ItemValue->TryGetObject(ItemObject) == false)
        {
            continue;
        }

        FString Name, Action, UniqueId, Reason;

        if ((*ItemObject)->TryGetStringField(TEXT("UniqueId"), UniqueId) == false ||
            (*ItemObject)->TryGetStringField(TEXT("Name"), Name) == false ||
            (*ItemObject)->TryGetStringField(TEXT("Action"), Action) == false ||
            (*ItemObject)->TryGetStringField(TEXT("Reason"), Reason) == false)
        {
            continue;
        }

        FLLMCommand Command;
        Command.Make
        (
            StringToCommandType(Action),
            Name,
            UniqueId,
            Reason
        );

        if (Command.IsValid() == true)
        {
            OutCommands.Add(Command);
        }
    }

    return (OutCommands.Num() > 0);
}