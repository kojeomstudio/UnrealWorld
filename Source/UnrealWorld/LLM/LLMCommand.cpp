#include "LLMCommand.h"

void FLLMCommand::Make(ELLMCommandType InCommandType, const FString& InTarget)
{
	CommandType = InCommandType;
	Target = InTarget;
}
