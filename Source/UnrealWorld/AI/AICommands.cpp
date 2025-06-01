#include "AICommands.h"

#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BrainComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

void FBaseAICommand::Execute(AAIController* Controller)
{
	if (UBrainComponent* BrainComp = Controller->GetBrainComponent())
	{
		if (UBlackboardComponent* BlackboardComp = BrainComp->GetBlackboardComponent())
		{
			BlackboardComp->SetValueAsBool("IsPatrol", false);
			BlackboardComp->SetValueAsBool("IsAttack", false);
			BlackboardComp->SetValueAsBool("IsIdle", false);
			BlackboardComp->SetValueAsBool("IsSpeakTo", false);
			BlackboardComp->SetValueAsBool("IsMoveTo", false);
			BlackboardComp->SetValueAsName("TargetName", FName());
		}
	}
}

void FMoveToCommand::Execute(AAIController* Controller)
{
	FBaseAICommand::Execute(Controller);

	if (UBrainComponent* BrainComp = Controller->GetBrainComponent())
	{
		if (UBlackboardComponent* BlackboardComp = BrainComp->GetBlackboardComponent())
		{
			BlackboardComp->SetValueAsBool("IsMoveTo", true);
			BlackboardComp->SetValueAsName("TargetName", FName(*Target));
		}
	}
}

void FAttackCommand::Execute(AAIController* Controller)
{
	FBaseAICommand::Execute(Controller);

	if (UBrainComponent* BrainComp = Controller->GetBrainComponent())
	{
		if (UBlackboardComponent* BlackboardComp = BrainComp->GetBlackboardComponent())
		{
			BlackboardComp->SetValueAsBool("IsAttack", true);
			BlackboardComp->SetValueAsName("TargetName", FName(*Target));
		}
	}
}

void FPatrolCommand::Execute(AAIController* Controller)
{
	FBaseAICommand::Execute(Controller);

	if (UBrainComponent* BrainComp = Controller->GetBrainComponent())
	{
		if (UBlackboardComponent* BlackboardComp = BrainComp->GetBlackboardComponent())
		{
			BlackboardComp->SetValueAsBool("IsPatrol", true);
		}
	}
}

void FIdleCommand::Execute(AAIController* Controller)
{
	FBaseAICommand::Execute(Controller);

	if (UBrainComponent* BrainComp = Controller->GetBrainComponent())
	{
		if (UBlackboardComponent* BlackboardComp = BrainComp->GetBlackboardComponent())
		{
			BlackboardComp->SetValueAsBool("IsIdle", true);
		}
	}
}

void FSpeakToCommand::Execute(AAIController* Controller)
{
	FBaseAICommand::Execute(Controller);

	if (UBrainComponent* BrainComp = Controller->GetBrainComponent())
	{
		if (UBlackboardComponent* BlackboardComp = BrainComp->GetBlackboardComponent())
		{
			BlackboardComp->SetValueAsBool("IsSpeakTo", true);
		}
	}
}
