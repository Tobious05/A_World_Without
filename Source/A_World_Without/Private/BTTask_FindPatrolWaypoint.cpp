// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Waypoint.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UBTTask_FindPatrolWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	//Checks which way the AIs should be moving
	bool bIsMovingLeft = OwnerComp.GetBlackboardComponent()->GetValueAsBool(FName("IsMovingLeft"));

	//Determines the tag being used based on the boolean being true or false
	FName TargetTag = bIsMovingLeft ? FName("Left") : FName("Right");

	//gets all the waypoints in the level
	TArray<AActor*> AllWaypoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaypoint::StaticClass(), AllWaypoints);

	//new list that includes all the waypoints with the correct tag
	TArray<AActor*> ValidWaypoints;
	for (AActor* WP : AllWaypoints)
	{
		if (WP->ActorHasTag(TargetTag))
		{
			ValidWaypoints.Add(WP);
		}
	}

	//picks random waypoint from filtered list
	if (ValidWaypoints.Num() > 0)
	{
		//picks a random waypoint
		int32 RandomIndex = FMath::RandRange(0, ValidWaypoints.Num() - 1);
		AActor* TargetWaypoint = ValidWaypoints[RandomIndex];

		//gets the navigation system
		UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		if (NavSys && TargetWaypoint)
		{
			FNavLocation RandomLocation;

			//Draws a 400 unit circle around the waypoint and gets valid location coordinates within it
			if (NavSys->GetRandomReachablePointInRadius(TargetWaypoint->GetActorLocation(), 400.0f, RandomLocation))
			{
				//save the new coordinate to the vector key "PatrolVector"
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("PatrolVector"), RandomLocation.Location);

				//reverses the boolean so the next time this task runs then the AIs walk the other way
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("IsMovingLeft"), !bIsMovingLeft);

				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}

