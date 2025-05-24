#include "AICommands.h"

#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

void FMoveToCommand::Execute(AAIController* Controller)
{
	if (UBlackboardComponent* BB = Controller->GetBlackboardComponent())
	{
		BB->SetValueAsName("TargetName", FName(*Target));
	}
}
