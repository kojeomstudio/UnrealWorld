#include "AICommands.h"

#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

void FMoveToCommand::Execute(AAIController* Controller)
{
	if (UBlackboardComponent* BB = Controller->GetBlackboardComponent())
	{
		BB->SetValueAsBool("IsPatrol", false);
		BB->SetValueAsName("TargetName", FName(*Target));
	}
}

void FAttackCommand::Execute(AAIController* Controller)
{
	if (UBlackboardComponent* BB = Controller->GetBlackboardComponent())
	{
		BB->SetValueAsBool("IsPatrol", false);
		BB->SetValueAsName("TargetName", FName(*Target));
	}
}

void FPatrolCommand::Execute(AAIController* Controller)
{
	if (UBlackboardComponent* BB = Controller->GetBlackboardComponent())
	{
		BB->SetValueAsBool("IsPatrol", true);
	}
}

void FIdleCommand::Execute(AAIController* Controller)
{
	if (UBlackboardComponent* BB = Controller->GetBlackboardComponent())
	{
		BB->SetValueAsBool("IsIdle", true);
	}
}

void FSpeakToCommand::Execute(AAIController* Controller)
{
	if (UBlackboardComponent* BB = Controller->GetBlackboardComponent())
	{
		BB->SetValueAsBool("IsSpeakTo", true);
		BB->SetValueAsName("TargetName", FName(*Target));
	}
}
