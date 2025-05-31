#include "LLMCommand.h"

void FLLMCommand::Make(EActorStateType InCommandType, const FString& InTarget, const FString& InUniqueId)
{
	CommandType = InCommandType;
	Target = InTarget;
	UniqueId = InUniqueId;
}
