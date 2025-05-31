#include "LLMCommand.h"

void FLLMCommand::Make(EActorStateType InCommandType, const FString& InTarget)
{
	CommandType = InCommandType;
	Target = InTarget;
}
