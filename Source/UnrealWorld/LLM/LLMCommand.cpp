#include "LLMCommand.h"

void FLLMCommand::Make(EActorStateType InCommandType, const FString& InTarget, const FString& InUniqueId, const FString& InReason)
{
	CommandType = InCommandType;
	Target = InTarget;
	UniqueId = InUniqueId;
	Reason = InReason;
}
