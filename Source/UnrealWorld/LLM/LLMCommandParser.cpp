#include "LLMCommandParser.h"
#include "LLMCommand.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#include "UnrealWorld/Common/UWEnums.h"
#include "UnrealWorld/AI/AICommands.h"

ELLMCommandType StringToCommandType(const FString& InStr)
{
	if (InStr.Equals("MoveTo", ESearchCase::IgnoreCase))
	{
		return ELLMCommandType::MoveTo;
	}
	else if (InStr.Equals("Attack", ESearchCase::IgnoreCase))
	{
		return ELLMCommandType::Attack;
	}
	else if (InStr.Equals("PlayAnimation", ESearchCase::IgnoreCase))
	{
		return ELLMCommandType::PlayAnimation;
	}
	else if (InStr.Equals("Speak", ESearchCase::IgnoreCase))
	{
		return ELLMCommandType::Speak;
	}

	return ELLMCommandType::Unknown;
}

bool FLLMCommandParser::Parse(const FString& JsonText, FLLMCommand& OutCommand)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonText);

	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		OutCommand.Make
		(
			StringToCommandType(JsonObject->GetStringField("command")),
			JsonObject->GetStringField("target")
		);

		// Return true only if the command has valid structure
		return OutCommand.IsValid();
	}

	// Parsing failed
	return false;
}

TSharedPtr<FBaseAICommand> FLLMCommandParser::ParseToCommandObject(const FString& JsonText)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonText);

	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		const FString Type = JsonObject->GetStringField("command");
		const FString Target = JsonObject->GetStringField("target");

		if (Type == "MoveTo")
		{
			return MakeShared<FMoveToCommand>(Target);
		}
		// Other types can follow...
	}

	return nullptr;
}
