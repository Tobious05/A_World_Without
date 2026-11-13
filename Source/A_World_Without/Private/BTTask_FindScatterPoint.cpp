// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindScatterPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UBTTask_FindScatterPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		APawn* AIPawn = AIController->GetPawn();
		if (AIPawn)
		{
			//Get the navigation system
			UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
			if (NavSys)
			{
				FNavLocation RandomLocation;
				//Draw a 800 unit circle radius around the AI and find a random reachable point
				if (NavSys->GetRandomReachablePointInRadius(AIPawn->GetActorLocation(), 800.0f, RandomLocation))
				{
					//Save the coordinate to a blackboard key named "ScatterVector"
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("ScatterVector"), RandomLocation.Location);
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}