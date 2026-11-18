// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindScatterPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UBTTask_FindScatterPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (AICon && AICon->GetPawn())
	{
		UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		if (NavSys)
		{
			//get AIs starting position
			FVector Origin = AICon->GetPawn()->GetActorLocation();

			//get a random 3D direction, make it 2D (so cant fly) and normalise to length of 1
			FVector RandomDir = FMath::VRand();
			RandomDir.Z = 0.0f;
			RandomDir.Normalize();

			//picks random distance between min of 3000 and max of 7000
			float RandomDistance = FMath::RandRange(1500.0f, 3000.0f);

			//multiply 1 unit direction by the random distance and add it to the AIs current location
			FVector IdealPoint = Origin + (RandomDir * RandomDistance);

			//Gets the NavMesh to snap the point to the nearest valid walking location
			FNavLocation FinalLocation;
			if (NavSys->ProjectPointToNavigation(IdealPoint, FinalLocation, FVector(500.0f, 500.0f, 500.0f)))
			{
				//save this distance point to the blacboard
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("ScatterVector"), FinalLocation.Location);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}